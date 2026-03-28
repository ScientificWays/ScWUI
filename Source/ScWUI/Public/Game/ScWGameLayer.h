// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "Widgets/ScWActivatableWidget.h"

#include "ScWGameLayer.generated.h"

#define MODULE_API SCWUI_API

class UScWControllerDisconnectedWidget;

/**
 *	Widget used to lay out the player's game layer (typically specified by an Add Widgets action in the experience)
 */
UCLASS(MinimalAPI, Abstract, BlueprintType, Blueprintable, meta = (DisplayName = "[ScW] Game Layer", Category = "ScW | Game"))
class UScWGameLayer : public UScWActivatableWidget
{
	GENERATED_BODY()

//~ Begin Initialize
public:

	UScWGameLayer(const FObjectInitializer& InObjectInitializer);

	virtual void NativeOnInitialized() override; // UUserWidget
	virtual void NativeDestruct() override; // UUserWidget
//~ End Initialize

//~ Begin Escape Menu
protected:
	void HandleEscapeAction();

	/** The menu to be displayed when the user presses the "Pause" or "Escape" button */
	UPROPERTY(Category = "Menus", EditDefaultsOnly)
	TSoftClassPtr<UCommonActivatableWidget> EscapeMenuClass;
//~ End Escape Menu

//~ Begin Controller Disconnect
protected:

	/**
	* Callback for when controllers are disconnected. Checks if the player has
	* no mapped input devices, and if so calls DisplayControllerDisconnectedMenu.
	*/
	void HandleInputDeviceConnectionChanged(EInputDeviceConnectionState NewConnectionState, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId);

	/**
	* Callback for when controllers change their owning platform user. Checks
	* if we no longer need to display the "Controller Disconnected" menu.
	*/
	void HandleInputDevicePairingChanged(FInputDeviceId InputDeviceId, FPlatformUserId NewUserPlatformId, FPlatformUserId OldUserPlatformId);

	/** Queue processing of controller state for next tick. */
	void NotifyControllerStateChangeForDisconnectScreen();

	/** Check connected controllers and show/hide the disconnect menu accordingly. */
	virtual void ProcessControllerDevicesHavingChangedForDisconnectScreen();

	/** Returns true if this platform supports a "controller disconnected" screen. */
	virtual bool ShouldPlatformDisplayControllerDisconnectedWidget() const;

	/** Pushes the ControllerDisconnectedMenuClass to the Menu layer (UI.Layer.Menu) */
	UFUNCTION(BlueprintNativeEvent, Category = "Controller Disconnect Menu")
	MODULE_API void DisplayControllerDisconnectedMenu();

	/** Hides the controller disconnected menu if it is active. */
	UFUNCTION(BlueprintNativeEvent, Category = "Controller Disconnect Menu")
	MODULE_API void HideControllerDisconnectedMenu();

	/** The widget class presented when all controllers are disconnected. */
	UPROPERTY(EditDefaultsOnly, Category = "Controller Disconnect Menu")
	TSubclassOf<UScWControllerDisconnectedWidget> ControllerDisconnectedScreen;

	/** Platform tags required to show the "Controller Disconnected" screen. */
	UPROPERTY(EditDefaultsOnly, Category = "Controller Disconnect Menu")
	FGameplayTagContainer PlatformRequiresControllerDisconnectedWidget;

	/** Pointer to the active "Controller Disconnected" menu if there is one. */
	UPROPERTY(Transient)
	TObjectPtr<UCommonActivatableWidget> SpawnedControllerDisconnectedWidget;

	/** Handle from the FSTicker for when we want to process the controller state of our player */
	FTSTicker::FDelegateHandle RequestProcessControllerStateHandle;
//~ End Controller Disconnect
};

#undef MODULE_API
