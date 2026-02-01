// Scientific Ways

#include "Messaging/ScWConfirmationWidget.h"

#include "Widgets/ScWButtonBase.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWConfirmationWidget)

void UScWConfirmationWidget::SetupDialog(UScWGameDialogDescriptor* InDescriptor, FCommonMessagingResultDelegate InResultCallback)
{
	Super::SetupDialog(InDescriptor, InResultCallback);

	Text_Title->SetText(InDescriptor->Header);
	RichText_Description->SetText(InDescriptor->Body);

	EntryBox_Buttons->Reset<UScWButtonBase>([](UScWButtonBase& InButton)
	{
		InButton.OnClicked().Clear();
	});
	for (const FScWConfirmationDialogAction& Action : InDescriptor->ButtonActions)
	{
		FDataTableRowHandle ActionRow;

		switch(Action.Result)
		{
			case EScWMessagingResult::Confirmed:
				ActionRow = ICommonInputModule::GetSettings().GetDefaultClickAction();
				break;
			case EScWMessagingResult::Declined:
				ActionRow = ICommonInputModule::GetSettings().GetDefaultBackAction();
				break;
			case EScWMessagingResult::Cancelled:
				ActionRow = CancelAction;
				break;
			default:
				ensure(false);
				continue;
		}
		UScWButtonBase* Button = EntryBox_Buttons->CreateEntry<UScWButtonBase>();
		Button->SetTriggeringInputAction(ActionRow);
		Button->OnClicked().AddUObject(this, &ThisClass::CloseConfirmationWindow, Action.Result);
		Button->SetButtonText(Action.OptionalDisplayText);
	}
	OnResultCallback = InResultCallback;
}

void UScWConfirmationWidget::KillDialog()
{
	Super::KillDialog();
}

void UScWConfirmationWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Border_TapToCloseZone->OnMouseButtonDownEvent.BindDynamic(this, &UScWConfirmationWidget::HandleTapToCloseZoneMouseButtonDown);
}

void UScWConfirmationWidget::CloseConfirmationWindow(EScWMessagingResult InResult)
{
	DeactivateWidget();
	OnResultCallback.ExecuteIfBound(InResult);
}

FEventReply UScWConfirmationWidget::HandleTapToCloseZoneMouseButtonDown(FGeometry InMyGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = FReply::Unhandled();

	if (InMouseEvent.IsTouchEvent() || InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		CloseConfirmationWindow(EScWMessagingResult::Declined);
		Reply.NativeReply = FReply::Handled();
	}
	return Reply;
}

#if WITH_EDITOR
void UScWConfirmationWidget::ValidateCompiledDefaults(IWidgetCompilerLog& InCompileLog) const
{
	if (CancelAction.IsNull())
	{
		InCompileLog.Error(FText::Format(FText::FromString(TEXT("{0} has unset property: CancelAction.")), FText::FromString(GetName())));
	}
}
#endif
