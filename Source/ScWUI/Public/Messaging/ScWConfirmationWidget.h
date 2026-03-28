// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "Messaging/CommonGameDialog.h"

#include "ScWConfirmationWidget.generated.h"

#define MODULE_API SCWUI_API

/**
 *	Confirmation dialog that dynamically creates action buttons and supports tap-to-close dismissal.
 */
UCLASS(MinimalAPI, Abstract, BlueprintType, Blueprintable, meta = (DisplayName = "[ScW] Confirmation Widget"))
class UScWConfirmationWidget : public UCommonGameDialog
{
	GENERATED_BODY()

//~ Begin Dialog
public:
	virtual void SetupDialog(UCommonGameDialogDescriptor* InDescriptor, FCommonMessagingResultDelegate InResultCallback) override; // UCommonGameDialog
	virtual void KillDialog() override; // UCommonGameDialog
protected:
	virtual void NativeOnInitialized() override; // UUserWidget
	virtual void CloseConfirmationWindow(ECommonMessagingResult InResult);
#if WITH_EDITOR
	virtual void ValidateCompiledDefaults(IWidgetCompilerLog& InCompileLog) const override; // UUserWidget
#endif
//~ End Dialog

//~ Begin Callbacks
private:

	UFUNCTION()
	FEventReply HandleTapToCloseZoneMouseButtonDown(FGeometry InMyGeometry, const FPointerEvent& InMouseEvent);

	FCommonMessagingResultDelegate OnResultCallback;
//~ End Callbacks

//~ Begin Bound Widgets
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
//~ End Bound Widgets
};

#undef MODULE_API
