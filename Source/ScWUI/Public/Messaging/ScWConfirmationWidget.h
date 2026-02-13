// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "Messaging/CommonGameDialog.h"

#include "ScWConfirmationWidget.generated.h"

/**
 *	
 */
UCLASS(MinimalAPI, Abstract, BlueprintType, Blueprintable)
class UScWConfirmationWidget : public UCommonGameDialog
{
	GENERATED_BODY()
public:
	virtual void SetupDialog(UCommonGameDialogDescriptor* InDescriptor, FCommonMessagingResultDelegate InResultCallback) override;
	virtual void KillDialog() override;

protected:
	virtual void NativeOnInitialized() override; // UUserWidget
	virtual void CloseConfirmationWindow(ECommonMessagingResult InResult);

#if WITH_EDITOR
	virtual void ValidateCompiledDefaults(IWidgetCompilerLog& InCompileLog) const override;
#endif

private:

	UFUNCTION()
	FEventReply HandleTapToCloseZoneMouseButtonDown(FGeometry InMyGeometry, const FPointerEvent& InMouseEvent);

	FCommonMessagingResultDelegate OnResultCallback;

private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> Text_Title;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock> RichText_Description;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UDynamicEntryBox> EntryBox_Buttons;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UCommonBorder> Border_TapToCloseZone;

	UPROPERTY(EditDefaultsOnly, meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle CancelAction;
};
