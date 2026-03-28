// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "ScWControllerDisconnectedWidget.generated.h"

#define MODULE_API SCWUI_API

class UHorizontalBox;
class UObject;
class UCommonButtonBase;
struct FPlatformUserSelectionCompleteParams;

/**
 * A screen to display when the user has had all of their controllers disconnected and needs to
 * re-connect them to continue playing the game.
 */
UCLASS(MinimalAPI, Abstract, BlueprintType, Blueprintable, meta = (DisplayName = "[ScW] Controller Disconnected Widget"))
class UScWControllerDisconnectedWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

//~ Begin Initialize
public:
	UScWControllerDisconnectedWidget(const FObjectInitializer& InObjectInitializer);
protected:
	virtual void NativeOnActivated() override; // UCommonActivatableWidget
//~ End Initialize

//~ Begin Change User
protected:
	virtual void HandleChangeUserClicked();

	/** Called when the user has changed after selecting the prompt to change platform users. */
	virtual void HandleChangeUserCompleted(const FPlatformUserSelectionCompleteParams& Params);

	/** Returns true if the Change User button should be displayed based on platform traits. */
	virtual bool ShouldDisplayChangeUserButton() const;

	/** Platform traits that, when met, will display the "Change User" button. */
	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer PlatformSupportsUserChangeTags;
//~ End Change User

//~ Begin Bound Widgets
protected:
	/** HBox containing the switch user button. Hidden on platforms without strict controller pairing. */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> HBox_SwitchUser;

	/** Button to handle changing the user on platforms with strict controller pairing. */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonButtonBase> Button_ChangeUser;
//~ End Bound Widgets
};

#undef MODULE_API