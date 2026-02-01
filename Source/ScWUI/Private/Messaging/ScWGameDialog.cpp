// Scientific Ways

#include "Messaging/ScWGameDialog.h"

#include "Messaging/ScWMessagingSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWGameDialog)

#define LOCTEXT_NAMESPACE "Messaging"

UScWGameDialogDescriptor* UScWGameDialogDescriptor::CreateConfirmationOk(const FText& Header, const FText& Body)
{
	UScWGameDialogDescriptor* Descriptor = NewObject<UScWGameDialogDescriptor>();
	Descriptor->Header = Header;
	Descriptor->Body = Body;

	FScWConfirmationDialogAction ConfirmAction;
	ConfirmAction.Result = EScWMessagingResult::Confirmed;
	ConfirmAction.OptionalDisplayText = LOCTEXT("Ok", "Ok");

	Descriptor->ButtonActions.Add(ConfirmAction);

	return Descriptor;
}

UScWGameDialogDescriptor* UScWGameDialogDescriptor::CreateConfirmationOkCancel(const FText& Header, const FText& Body)
{
	UScWGameDialogDescriptor* Descriptor = NewObject<UScWGameDialogDescriptor>();
	Descriptor->Header = Header;
	Descriptor->Body = Body;

	FScWConfirmationDialogAction ConfirmAction;
	ConfirmAction.Result = EScWMessagingResult::Confirmed;
	ConfirmAction.OptionalDisplayText = LOCTEXT("Ok", "Ok");

	FScWConfirmationDialogAction CancelAction;
	CancelAction.Result = EScWMessagingResult::Cancelled;
	CancelAction.OptionalDisplayText = LOCTEXT("Cancel", "Cancel");

	Descriptor->ButtonActions.Add(ConfirmAction);
	Descriptor->ButtonActions.Add(CancelAction);

	return Descriptor;
}

UScWGameDialogDescriptor* UScWGameDialogDescriptor::CreateConfirmationYesNo(const FText& Header, const FText& Body)
{
	UScWGameDialogDescriptor* Descriptor = NewObject<UScWGameDialogDescriptor>();
	Descriptor->Header = Header;
	Descriptor->Body = Body;

	FScWConfirmationDialogAction ConfirmAction;
	ConfirmAction.Result = EScWMessagingResult::Confirmed;
	ConfirmAction.OptionalDisplayText = LOCTEXT("Yes", "Yes");

	FScWConfirmationDialogAction DeclineAction;
	DeclineAction.Result = EScWMessagingResult::Declined;
	DeclineAction.OptionalDisplayText = LOCTEXT("No", "No");

	Descriptor->ButtonActions.Add(ConfirmAction);
	Descriptor->ButtonActions.Add(DeclineAction);

	return Descriptor;
}

UScWGameDialogDescriptor* UScWGameDialogDescriptor::CreateConfirmationYesNoCancel(const FText& Header, const FText& Body)
{
	UScWGameDialogDescriptor* Descriptor = NewObject<UScWGameDialogDescriptor>();
	Descriptor->Header = Header;
	Descriptor->Body = Body;

	FScWConfirmationDialogAction ConfirmAction;
	ConfirmAction.Result = EScWMessagingResult::Confirmed;
	ConfirmAction.OptionalDisplayText = LOCTEXT("Yes", "Yes");

	FScWConfirmationDialogAction DeclineAction;
	DeclineAction.Result = EScWMessagingResult::Declined;
	DeclineAction.OptionalDisplayText = LOCTEXT("No", "No");

	FScWConfirmationDialogAction CancelAction;
	CancelAction.Result = EScWMessagingResult::Cancelled;
	CancelAction.OptionalDisplayText = LOCTEXT("Cancel", "Cancel");

	Descriptor->ButtonActions.Add(ConfirmAction);
	Descriptor->ButtonActions.Add(DeclineAction);
	Descriptor->ButtonActions.Add(CancelAction);

	return Descriptor;
}

UScWGameDialog::UScWGameDialog()
{

}

void UScWGameDialog::SetupDialog(UScWGameDialogDescriptor* Descriptor, FCommonMessagingResultDelegate ResultCallback)
{

}

void UScWGameDialog::KillDialog()
{

}

#undef LOCTEXT_NAMESPACE
