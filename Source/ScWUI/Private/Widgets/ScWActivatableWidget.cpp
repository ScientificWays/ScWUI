// Scientific Ways

#include "Widgets/ScWActivatableWidget.h"

#include "Player/ScWPlayerController.h"

#include "Game/ScWGamePauseSubsystem.h"

#include "Input/ScWInputFunctionLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWActivatableWidget)

#define LOCTEXT_NAMESPACE "ScW"

UScWActivatableWidget::UScWActivatableWidget(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
	//InputMappingContextPriority = 1;
}

//~ Begin Initialize
void UScWActivatableWidget::NativePreConstruct() // UUserWidget
{
	if (!IsDesignTime())
	{
		AScWPlayerController* OwningPlayer = Cast<AScWPlayerController>(GetOwningPlayer());
		ensureReturn(OwningPlayer);

		if (InputMappingContext)
		{
			UScWInputFunctionLibrary::AddEnhancedInputMappingContextTo(OwningPlayer, InputMappingContext, InputMappingContextPriority, InputMappingContextOptions);
		}
		if (bShouldShowMouseCursor)
		{
			OwningPlayer->AddShowMouseCursorSource(this);
		}
		if (bShouldBlockMovementInput)
		{
			OwningPlayer->AddMovementInputBlockSource(this);
		}
		if (bShouldBlockLookInput)
		{
			OwningPlayer->AddLookInputBlockSource(this);
		}
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
				UE_LOG(LogScWUI, Error, TEXT("%hs world should have UScWGamePauseSubsystem for widget to work properly!"), __func__);
			}
		}
	}
	Super::NativePreConstruct();
}

void UScWActivatableWidget::NativeDestruct() // UUserWidget
{
	if (!IsDesignTime())
	{
		AScWPlayerController* OwningPlayer = Cast<AScWPlayerController>(GetOwningPlayer());
		ensureReturn(OwningPlayer);

		if (InputMappingContext)
		{
			UScWInputFunctionLibrary::RemoveEnhancedInputMappingContextFrom(OwningPlayer, InputMappingContext, InputMappingContextOptions);
		}
		if (bShouldShowMouseCursor)
		{
			OwningPlayer->RemoveShowMouseCursorSource(this);
		}
		if (bShouldBlockMovementInput)
		{
			OwningPlayer->RemoveMovementInputBlockSource(this);
		}
		if (bShouldBlockLookInput)
		{
			OwningPlayer->RemoveLookInputBlockSource(this);
		}
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
				UE_LOG(LogScWUI, Error, TEXT("%hs world should have UScWGamePauseSubsystem for widget to work properly!"), __func__);
			}
		}
	}
	Super::NativeDestruct();
}

TOptional<FUIInputConfig> UScWActivatableWidget::GetDesiredInputConfig() const
{
	switch (InputConfig)
	{
		case EScWWidgetInputMode::GameAndMenu:
			return FUIInputConfig(ECommonInputMode::All, GameMouseCaptureMode);
		case EScWWidgetInputMode::Game:
			return FUIInputConfig(ECommonInputMode::Game, GameMouseCaptureMode);
		case EScWWidgetInputMode::Menu:
			return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
		case EScWWidgetInputMode::Default:
		default:
			return TOptional<FUIInputConfig>();
	}
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

void UScWActivatableWidget::BP_RemoveAnimated_Implementation()
{
	UE_LOG(LogScWUI, Error, TEXT("%hs is not implemented on %s!"), __func__, *GetName());
}
//~ End Initialize

#undef LOCTEXT_NAMESPACE
