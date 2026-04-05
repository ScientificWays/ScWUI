// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "Input/UIActionBindingHandle.h"

#include "ScWActivatableWidget.generated.h"

#define MODULE_API SCWUI_API

/**
 *	Gameplay message payload broadcast when an activatable widget is activated or deactivated.
 */
USTRUCT(BlueprintType)
struct FGameplayMessage_Widget_Activatable
{
	GENERATED_BODY()

	UPROPERTY(Category = "Widget", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UScWActivatableWidget> Widget;
};

/**
 *	Activatable widget that drives input config, game pause, and gameplay message broadcasts on activation.
 */
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

	UPROPERTY(Category = "Input", EditAnywhere, BlueprintReadOnly, meta = (InlineEditConditionToggle))
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

#undef MODULE_API
