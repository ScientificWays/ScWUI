// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "ScWButtonBase.generated.h"

UCLASS(MinimalAPI, Abstract, BlueprintType, Blueprintable)
class UScWButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	MODULE_API void SetButtonText(const FText& InText);
	
protected:
	virtual void NativePreConstruct() override; // UUserWidget
	virtual void UpdateInputActionWidget() override; // UCommonButtonBase
	virtual void OnInputMethodChanged(ECommonInputType InCurrentInputType) override; // UCommonButtonBase

	void RefreshButtonText();
	
	UFUNCTION(BlueprintImplementableEvent)
	MODULE_API void UpdateButtonText(const FText& InText);

	UFUNCTION(BlueprintImplementableEvent)
	MODULE_API void UpdateButtonStyle();
	
private:
	UPROPERTY(EditAnywhere, Category="Button", meta=(InlineEditConditionToggle))
	uint8 bOverride_ButtonText : 1;
	
	UPROPERTY(EditAnywhere, Category="Button", meta=( editcondition="bOverride_ButtonText" ))
	FText ButtonText;
};
