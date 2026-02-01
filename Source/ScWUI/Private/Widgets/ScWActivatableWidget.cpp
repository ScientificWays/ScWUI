// Scientific Ways

#include "Widgets/ScWActivatableWidget.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWActivatableWidget)

#define LOCTEXT_NAMESPACE "ScW"

UScWActivatableWidget::UScWActivatableWidget(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{

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

#undef LOCTEXT_NAMESPACE
