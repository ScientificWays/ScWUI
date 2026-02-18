// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "Input/UIActionBindingHandle.h"

#include "ScWActivatableWidget.generated.h"

// An activatable widget that automatically drives the desired input config when activated
UCLASS(MinimalAPI, Abstract, Blueprintable, meta = (DisplayName = "[ScW] Activatable Widget"))
class UScWActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
//~ Begin Initialize
public:
	UScWActivatableWidget(const FObjectInitializer& InObjectInitializer);
protected:
	virtual void NativeOnActivated() override; // UCommonActivatableWidget
	virtual void NativeOnDeactivated() override; // UCommonActivatableWidget
public:
#if WITH_EDITOR
	virtual void ValidateCompiledWidgetTree(const UWidgetTree& InBlueprintWidgetTree, class IWidgetCompilerLog& InCompilerLog) const override; // UserWidget
#endif

	UFUNCTION(Category = "Initialize", BlueprintCallable)
	void RemoveAnimated();

	UFUNCTION(Category = "Initialize", BlueprintNativeEvent, meta = (DisplayName = "Remove Animated"))
	void BP_HandleRemoveAnimated();
//~ End Initialize
	
//~ Begin Input
public:
	virtual TOptional<struct FUIInputConfig> GetDesiredInputConfig() const override; // UCommonActivatableWidget

	UPROPERTY(Category = "Input", EditAnywhere, BlueprintReadOnly)
	bool bUseCustomInputConfig;

	UPROPERTY(Category = "Input", EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bUseCustomInputConfig"))
	FUIInputConfig CustomInputConfig;
//~ End Input
	
//~ Begin Game
public:

	UPROPERTY(Category = "Game", EditAnywhere, BlueprintReadOnly)
	bool bShouldPauseGame;

	UPROPERTY(Category = "Game", EditAnywhere, BlueprintReadOnly)
	bool bUnpauseOnRemovingAnimated;
//~ End Game
};
