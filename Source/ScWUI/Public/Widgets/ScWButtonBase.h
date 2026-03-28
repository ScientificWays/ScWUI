// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "ScWButtonBase.generated.h"

#define MODULE_API SCWUI_API

/**
 *	Base button with text management, input-method-aware styling, and action widget integration.
 */
UCLASS(MinimalAPI, Abstract, BlueprintType, Blueprintable, meta = (DisplayName = "[ScW] Button Base"))
class UScWButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

//~ Begin Button API
public:

	UFUNCTION(Category = "Button", BlueprintCallable)
	MODULE_API void SetButtonText(const FText& InText);

protected:
	void RefreshButtonText();

	UFUNCTION(Category = "Button", BlueprintImplementableEvent, meta = (DisplayName = "Update Button Text"))
	MODULE_API void BP_UpdateButtonText(const FText& InText);

	UFUNCTION(Category = "Button", BlueprintImplementableEvent, meta = (DisplayName = "Update Button Style"))
	MODULE_API void BP_UpdateButtonStyle();
//~ End Button API

//~ Begin Overrides
protected:
	virtual void NativePreConstruct() override; // UUserWidget
	virtual void UpdateInputActionWidget() override; // UCommonButtonBase
	virtual void OnInputMethodChanged(ECommonInputType InCurrentInputType) override; // UCommonButtonBase
//~ End Overrides

//~ Begin Data
private:

	UPROPERTY(Category = "Button", EditAnywhere, meta = (InlineEditConditionToggle))
	uint8 bOverride_ButtonText : 1;

	UPROPERTY(Category = "Button", EditAnywhere, meta = (EditCondition = "bOverride_ButtonText"))
	FText ButtonText;
//~ End Data
};

#undef MODULE_API
