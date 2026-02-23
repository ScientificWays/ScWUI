// Scientific Ways

#include "Widgets/ScWActivatableWidget.h"

#include "Tags/ScWUITags.h"

#include "Game/ScWGamePauseSubsystem.h"
#include "GameFramework/GameplayMessageSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWActivatableWidget)

#define LOCTEXT_NAMESPACE "ScW"

//~ Begin Initialize
UScWActivatableWidget::UScWActivatableWidget(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
	bUseCustomInputConfig = false;

	CustomInputConfig = FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture, EMouseLockMode::DoNotLock, false);
	CustomInputConfig.bIgnoreMoveInput = true;
	CustomInputConfig.bIgnoreLookInput = true;

	bUnpauseOnRemovingAnimated = true;
}

void UScWActivatableWidget::NativeOnActivated() // UCommonActivatableWidget
{
	Super::NativeOnActivated();

	if (!IsDesignTime())
	{
		UWorld* World = GetWorld();
		ensureReturn(World);
		
		if (bShouldPauseGame)
		{
			if (UScWGamePauseSubsystem* GamePauseSubsystem = World->GetSubsystem<UScWGamePauseSubsystem>())
			{
				GamePauseSubsystem->AddPauseSourceObject(this);
			}
			else
			{
				UE_LOG(LogScWUI, Error, TEXT("%hs world should have UScWGamePauseSubsystem for widget to work properly!"), __FUNCTION__);
			}
		}
		UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(this);
		FGameplayMessage_Widget_Activatable ActivatedMessage = { this };
		GameplayMessageSubsystem.BroadcastMessage(FScWUITags::GameplayMessage_Widget_Activatable_Activated, ActivatedMessage);
	}
}

void UScWActivatableWidget::NativeOnDeactivated() // UCommonActivatableWidget
{
	if (!IsDesignTime())
	{
		UWorld* World = GetWorld();
		ensureReturn(World);

		if (bShouldPauseGame)
		{
			if (UScWGamePauseSubsystem* GamePauseSubsystem = World->GetSubsystem<UScWGamePauseSubsystem>())
			{
				GamePauseSubsystem->RemovePauseSourceObject(this);
			}
			else
			{
				UE_LOG(LogScWUI, Error, TEXT("%hs world should have UScWGamePauseSubsystem for widget to work properly!"), __FUNCTION__);
			}
		}
		UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(this);
		FGameplayMessage_Widget_Activatable DeactivatedMessage = { this };
		GameplayMessageSubsystem.BroadcastMessage(FScWUITags::GameplayMessage_Widget_Activatable_Deactivated, DeactivatedMessage);
	}
	Super::NativeOnDeactivated();
}

#if WITH_EDITOR

void UScWActivatableWidget::ValidateCompiledWidgetTree(const UWidgetTree& InBlueprintWidgetTree, class IWidgetCompilerLog& InCompilerLog) const
{
	Super::ValidateCompiledWidgetTree(InBlueprintWidgetTree, InCompilerLog);

	if (!GetClass()->IsFunctionImplementedInScript(GET_FUNCTION_NAME_CHECKED(UScWActivatableWidget, BP_GetDesiredFocusTarget)))
	{
		if (GetParentNativeClass(GetClass()) == UScWActivatableWidget::StaticClass())
		{
			InCompilerLog.Warning(LOCTEXT("ValidateGetDesiredFocusTarget_Warning", "GetDesiredFocusTarget wasn't implemented, you're going to have trouble using gamepads on this screen."));
		}
		else
		{
			//TODO - Note for now, because we can't guarantee it isn't implemented in a native subclass of this one.
			InCompilerLog.Note(LOCTEXT("ValidateGetDesiredFocusTarget_Note", "GetDesiredFocusTarget wasn't implemented, you're going to have trouble using gamepads on this screen. If it was implemented in the native base class you can ignore this message."));
		}
	}
}

#endif

void UScWActivatableWidget::RemoveAnimated()
{
	if (bShouldPauseGame && bUnpauseOnRemovingAnimated)
	{
		UWorld* World = GetWorld();
		ensureReturn(World);

		if (UScWGamePauseSubsystem* GamePauseSubsystem = World->GetSubsystem<UScWGamePauseSubsystem>())
		{
			GamePauseSubsystem->RemovePauseSourceObject(this);
		}
		else
		{
			UE_LOG(LogScWUI, Error, TEXT("%hs world should have UScWGamePauseSubsystem for widget to work properly!"), __FUNCTION__);
		}
	}
	BP_HandleRemoveAnimated();
}

void UScWActivatableWidget::BP_HandleRemoveAnimated_Implementation()
{
	UE_LOG(LogScWUI, Error, TEXT("%hs is not implemented on %s!"), __FUNCTION__, *GetName());
}
//~ End Initialize

//~ Begin Input
TOptional<FUIInputConfig> UScWActivatableWidget::GetDesiredInputConfig() const // UCommonActivatableWidget
{
	if (GetClass()->IsFunctionImplementedInScript(GET_FUNCTION_NAME_CHECKED(ThisClass, BP_GetDesiredInputConfig)))
	{
		return BP_GetDesiredInputConfig();
	}
	else if (bUseCustomInputConfig)
	{
		return CustomInputConfig;
	}
	return TOptional<FUIInputConfig>();
}
//~ End Input

#undef LOCTEXT_NAMESPACE
