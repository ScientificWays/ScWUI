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

public:
	UScWActivatableWidget(const FObjectInitializer& InObjectInitializer);
protected:

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
};
