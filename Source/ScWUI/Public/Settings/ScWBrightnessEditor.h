// Scientific Ways

#pragma once

#include "CommonActivatableWidget.h"
#include "Widgets/IGameSettingActionInterface.h"

#include "ScWBrightnessEditor.generated.h"

#define MODULE_API SCWUI_API

enum class ECommonInputType : uint8;

class UCommonButtonBase;
class UCommonRichTextBlock;
class UGameSetting;
class UGameSettingValueScalar;
class UObject;
class UWidgetSwitcher;
struct FAnalogInputEvent;
struct FFrame;
struct FGameplayTag;
struct FGeometry;
struct FPointerEvent;

/**
 *	Brightness adjustment widget driven by analog stick and mouse wheel input.
 */
UCLASS(MinimalAPI, Abstract, meta = (DisplayName = "[ScW] Brightness Editor"))
class UScWBrightnessEditor : public UCommonActivatableWidget, public IGameSettingActionInterface
{
	GENERATED_BODY()

//~ Begin Initialize
public:
	FSimpleMulticastDelegate OnSafeZoneSet;

public:
	UScWBrightnessEditor(const FObjectInitializer& InObjectInitializer);

	virtual bool ExecuteActionForSetting_Implementation(FGameplayTag ActionTag, UGameSetting* InSetting) override; // IGameSettingActionInterface
//~ End Initialize

//~ Begin Overrides
protected:

	UPROPERTY(EditAnywhere, Category = "Restrictions")
	bool bCanCancel = true;

	virtual void NativeOnActivated() override; // UCommonActivatableWidget
	virtual void NativeOnInitialized() override; // UUserWidget
	virtual FReply NativeOnAnalogValueChanged(const FGeometry& InGeometry, const FAnalogInputEvent& InAnalogEvent) override; // UUserWidget
	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override; // UUserWidget

	void HandleInputModeChanged(ECommonInputType InInputType);
//~ End Overrides

//~ Begin Callbacks
private:
	UFUNCTION()
	void HandleBackClicked();

	UFUNCTION()
	void HandleDoneClicked();

	TWeakObjectPtr<UGameSettingValueScalar> ValueSetting;
//~ End Callbacks

//~ Begin Bound Widgets
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UWidgetSwitcher> Switcher_SafeZoneMessage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UCommonRichTextBlock> RichText_Default;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UCommonButtonBase> Button_Back;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UCommonButtonBase> Button_Done;
//~ End Bound Widgets
};

#undef MODULE_API
