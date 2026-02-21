// Scientific Ways

#include "Game/ScWGameLayer.h"

#include "CommonUIExtensions.h"

#include "Tags/ScWUITags.h"

#include "Messaging/ScWControllerDisconnectedWidget.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWGameLayer)

UScWGameLayer::UScWGameLayer(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
	, SpawnedControllerDisconnectedWidget(nullptr)
{
	bUseCustomInputConfig = true;

	CustomInputConfig = FUIInputConfig(ECommonInputMode::Game, EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown, EMouseLockMode::LockAlways, false);
	CustomInputConfig.bIgnoreMoveInput = false;
	CustomInputConfig.bIgnoreLookInput = false;

	// By default, only primary controller platforms require a disconnect screen. 
	PlatformRequiresControllerDisconnectedWidget.AddTag(FScWUITags::Platform_Trait_Input_PrimaryController);
}

void UScWGameLayer::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	RegisterUIActionBinding(FBindUIActionArgs(FUIActionTag::ConvertChecked(FScWUITags::UI_Action_Escape), false, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleEscapeAction)));

	// If we can display a controller disconnect screen, then listen for the controller state change delegates
	if (ShouldPlatformDisplayControllerDisconnectedWidget())
	{
		// Bind to when input device connections change
		IPlatformInputDeviceMapper& DeviceMapper = IPlatformInputDeviceMapper::Get();
		DeviceMapper.GetOnInputDeviceConnectionChange().AddUObject(this, &ThisClass::HandleInputDeviceConnectionChanged);
		DeviceMapper.GetOnInputDevicePairingChange().AddUObject(this, &ThisClass::HandleInputDevicePairingChanged);	
	}
}

void UScWGameLayer::NativeDestruct()
{
	Super::NativeDestruct();

	// Remove bindings to input device connection changing
	IPlatformInputDeviceMapper& DeviceMapper = IPlatformInputDeviceMapper::Get();
	DeviceMapper.GetOnInputDeviceConnectionChange().RemoveAll(this);
	DeviceMapper.GetOnInputDevicePairingChange().RemoveAll(this);

	if (RequestProcessControllerStateHandle.IsValid())
	{
		FTSTicker::GetCoreTicker().RemoveTicker(RequestProcessControllerStateHandle);
		RequestProcessControllerStateHandle.Reset();
	}
}

void UScWGameLayer::HandleEscapeAction()
{
	if (ensure(!EscapeMenuClass.IsNull()))
	{
		UCommonUIExtensions::PushStreamedContentToLayer_ForPlayer(GetOwningLocalPlayer(), FScWUITags::UI_Layer_Menu, EscapeMenuClass);
	}
}

void UScWGameLayer::HandleInputDeviceConnectionChanged(EInputDeviceConnectionState NewConnectionState, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId)
{
	const FPlatformUserId OwningLocalPlayerId = GetOwningLocalPlayer()->GetPlatformUserId();

	ensure(OwningLocalPlayerId.IsValid());

	// This device connection change happened to a different player, ignore it for us.
	if (PlatformUserId != OwningLocalPlayerId)
	{
		return;
	}
	NotifyControllerStateChangeForDisconnectScreen();
}

void UScWGameLayer::HandleInputDevicePairingChanged(FInputDeviceId InputDeviceId, FPlatformUserId NewUserPlatformId, FPlatformUserId OldUserPlatformId)
{
	const FPlatformUserId OwningLocalPlayerId = GetOwningLocalPlayer()->GetPlatformUserId();

	ensure(OwningLocalPlayerId.IsValid());

	// If this pairing change was related to our local player, notify of a change.
	if (NewUserPlatformId == OwningLocalPlayerId || OldUserPlatformId == OwningLocalPlayerId)
	{
		NotifyControllerStateChangeForDisconnectScreen();	
	}
}

bool UScWGameLayer::ShouldPlatformDisplayControllerDisconnectedWidget() const
{
	// We only want this menu on primarily controller platforms
	bool bHasAllRequiredTags = ICommonUIModule::GetSettings().GetPlatformTraits().HasAll(PlatformRequiresControllerDisconnectedWidget);

	// Check the tags that we may be emulating in the editor too
#if WITH_EDITOR
	const FGameplayTagContainer& PlatformEmulationTags = UCommonUIVisibilitySubsystem::Get(GetOwningLocalPlayer())->GetVisibilityTags();
	bHasAllRequiredTags |= PlatformEmulationTags.HasAll(PlatformRequiresControllerDisconnectedWidget);
#endif	// WITH_EDITOR
	return bHasAllRequiredTags;
}

void UScWGameLayer::NotifyControllerStateChangeForDisconnectScreen()
{
	// We should only ever get here if we have bound to the controller state change delegates
	ensure(ShouldPlatformDisplayControllerDisconnectedWidget());

	// If we haven't already, queue the processing of device state for next tick.
	if (!RequestProcessControllerStateHandle.IsValid())
	{
		RequestProcessControllerStateHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateWeakLambda(this, [this](float DeltaTime)
		{
			RequestProcessControllerStateHandle.Reset();
			ProcessControllerDevicesHavingChangedForDisconnectScreen();
			return false;
		}));
	}
}

void UScWGameLayer::ProcessControllerDevicesHavingChangedForDisconnectScreen()
{
	// We should only ever get here if we have bound to the controller state change delegates
	ensure(ShouldPlatformDisplayControllerDisconnectedWidget());
	
	const FPlatformUserId OwningLocalPlayerId = GetOwningLocalPlayer()->GetPlatformUserId();
	
	ensure(OwningLocalPlayerId.IsValid());

	// Get all input devices mapped to our player
	const IPlatformInputDeviceMapper& DeviceMapper = IPlatformInputDeviceMapper::Get();
    TArray<FInputDeviceId> MappedInputDevices;
    const int32 NumDevicesMappedToUser = DeviceMapper.GetAllInputDevicesForUser(OwningLocalPlayerId, OUT MappedInputDevices);

    // Check if there are any other connected GAMEPAD devices mapped to this platform user. 
    bool bHasConnectedController = false;

    for (const FInputDeviceId MappedDevice : MappedInputDevices)
    {
    	if (DeviceMapper.GetInputDeviceConnectionState(MappedDevice) == EInputDeviceConnectionState::Connected)
    	{
    		const FHardwareDeviceIdentifier HardwareInfo = UInputDeviceSubsystem::Get()->GetInputDeviceHardwareIdentifier(MappedDevice);
    		if (HardwareInfo.PrimaryDeviceType == EHardwareDevicePrimaryType::Gamepad)
    		{
    			bHasConnectedController = true;
    		}
    	}			
    }
    // If there are no gamepad input devices mapped to this user, then we want to pop the toast saying to re-connect them
    if (!bHasConnectedController)
    {
    	DisplayControllerDisconnectedMenu();
    }
	// Otherwise we can hide the screen if it is currently being shown
	else if (SpawnedControllerDisconnectedWidget)
	{
		HideControllerDisconnectedMenu();
	}
}

void UScWGameLayer::DisplayControllerDisconnectedMenu_Implementation()
{
	UE_LOG(LogScWUI, Log, TEXT("[%hs] Display controller disconnected menu!"), __FUNCTION__);

	if (ControllerDisconnectedScreen)
	{
		// Push the "controller disconnected" widget to the menu layer
		SpawnedControllerDisconnectedWidget = UCommonUIExtensions::PushContentToLayer_ForPlayer(GetOwningLocalPlayer(), FScWUITags::UI_Layer_Menu, ControllerDisconnectedScreen);
	}
}

void UScWGameLayer::HideControllerDisconnectedMenu_Implementation()
{
	UE_LOG(LogScWUI, Log, TEXT("[%hs] Hide controller disconnected menu!"), __FUNCTION__);
	
	UCommonUIExtensions::PopContentFromLayer(SpawnedControllerDisconnectedWidget);
	SpawnedControllerDisconnectedWidget = nullptr;
}