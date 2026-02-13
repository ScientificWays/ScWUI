// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "ScWActivatableWidget.generated.h"

UENUM(BlueprintType, meta = (DisplayName = "[ScW] Widget Input Mode"))
enum class EScWWidgetInputMode : uint8
{
	Default,
	GameAndMenu,
	Game,
	Menu
};

// An activatable widget that automatically drives the desired input config when activated
UCLASS(MinimalAPI, Abstract, Blueprintable, meta = (DisplayName = "[ScW] Activatable Widget"))
class UScWActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
//~ Begin Initialize
public:
	UScWActivatableWidget(const FObjectInitializer& InObjectInitializer);
protected:
	virtual void NativePreConstruct() override; // UUserWidget
	virtual void NativeDestruct() override; // UUserWidget

	/** The desired input mode to use while this UI is activated, for example do you want key presses to still reach the game/player controller? */
	UPROPERTY(EditDefaultsOnly, Category = Input)
	EScWWidgetInputMode InputConfig = EScWWidgetInputMode::Default;

	/** The desired mouse behavior when the game gets input. */
	UPROPERTY(EditDefaultsOnly, Category = Input)
	EMouseCaptureMode GameMouseCaptureMode = EMouseCaptureMode::CapturePermanently;
public:
	virtual TOptional<struct FUIInputConfig> GetDesiredInputConfig() const override; // UCommonActivatableWidget
#if WITH_EDITOR
	virtual void ValidateCompiledWidgetTree(const UWidgetTree& InBlueprintWidgetTree, class IWidgetCompilerLog& InCompilerLog) const override; // UserWidget
#endif

	UFUNCTION(Category = "Initialize", BlueprintCallable, BlueprintNativeEvent, meta = (DisplayName = "Remove Animated"))
	void BP_RemoveAnimated();
//~ End Initialize
	
//~ Begin Input
public:

	UPROPERTY(Category = "Input", EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(Category = "Input", EditAnywhere, BlueprintReadOnly)
	int32 InputMappingContextPriority;

	UPROPERTY(Category = "Input", EditAnywhere, BlueprintReadOnly)
	FModifyContextOptions InputMappingContextOptions;

	UPROPERTY(Category = "Input", EditAnywhere, BlueprintReadOnly)
	bool bShouldShowMouseCursor;

	UPROPERTY(Category = "Input", EditAnywhere, BlueprintReadOnly)
	bool bShouldBlockMovementInput;

	UPROPERTY(Category = "Input", EditAnywhere, BlueprintReadOnly)
	bool bShouldBlockLookInput;
//~ End Input
	
//~ Begin Game
public:

	UPROPERTY(Category = "Game", EditAnywhere, BlueprintReadOnly)
	bool bShouldPauseGame;
//~ End Game
};
