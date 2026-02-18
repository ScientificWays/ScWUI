// Scientific Ways

#include "Messaging/ScWControllerDisconnectedWidget.h"

#include "Tags/ScWUITags.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWControllerDisconnectedWidget)

UScWControllerDisconnectedWidget::UScWControllerDisconnectedWidget(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
	// By default, only strict pairing platforms will need this button.
	PlatformSupportsUserChangeTags.AddTag(FScWUITags::Platform_Trait_Input_HasStrictControllerPairing);
}

void UScWControllerDisconnectedWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	if (!HBox_SwitchUser)
	{
		UE_LOG(LogScWUI, Error, TEXT("Unable to find HBox_SwitchUser on Widget %s"), *GetNameSafe(this));
		return;
	}
	if (!Button_ChangeUser)
	{
		UE_LOG(LogScWUI, Error, TEXT("Unable to find Button_ChangeUser on Widget %s"), *GetNameSafe(this));
		return;
	}
	HBox_SwitchUser->SetVisibility(ESlateVisibility::Collapsed);
	Button_ChangeUser->SetVisibility(ESlateVisibility::Hidden);

	if (ShouldDisplayChangeUserButton())
	{
		// This is the platform user for "unpaired" input devices. Not every platform supports this, so
		// only set this to visible if the unpaired user is valid.
		const FPlatformUserId UnpairedUserId = IPlatformInputDeviceMapper::Get().GetUserForUnpairedInputDevices();
		if (UnpairedUserId.IsValid())
		{
			HBox_SwitchUser->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			Button_ChangeUser->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}		
	}
	Button_ChangeUser->OnClicked().AddUObject(this, &ThisClass::HandleChangeUserClicked);
}

bool UScWControllerDisconnectedWidget::ShouldDisplayChangeUserButton() const
{
	bool bRequiresChangeUserButton = ICommonUIModule::GetSettings().GetPlatformTraits().HasAll(PlatformSupportsUserChangeTags);

	// Check the tags that we may be emulating in the editor too
#if WITH_EDITOR
	const FGameplayTagContainer& PlatformEmulationTags = UCommonUIVisibilitySubsystem::Get(GetOwningLocalPlayer())->GetVisibilityTags();
	bRequiresChangeUserButton |= PlatformEmulationTags.HasAll(PlatformSupportsUserChangeTags);
#endif	// WITH_EDITOR

	return bRequiresChangeUserButton;
}

void UScWControllerDisconnectedWidget::HandleChangeUserClicked()
{
	ensure(ShouldDisplayChangeUserButton());

	UE_LOG(LogScWUI, Log, TEXT("[%hs] Change user requested!"), __FUNCTION__);

	const FPlatformUserId OwningPlayerId = GetOwningLocalPlayer()->GetPlatformUserId();
	const FInputDeviceId DeviceId = IPlatformInputDeviceMapper::Get().GetPrimaryInputDeviceForUser(OwningPlayerId);

	FGenericPlatformApplicationMisc::ShowPlatformUserSelector(
		DeviceId,
		EPlatformUserSelectorFlags::Default,
		[this](const FPlatformUserSelectionCompleteParams& Params)
		{
			HandleChangeUserCompleted(Params);
		});
}

void UScWControllerDisconnectedWidget::HandleChangeUserCompleted(const FPlatformUserSelectionCompleteParams& Params)
{
	UE_LOG(LogScWUI, Log, TEXT("[%hs] User change complete!"), __FUNCTION__);

	// TODO: Handle any user changing logic in your game here
}