// Scientific Ways

#pragma once

#include "Widgets/GameSettingListEntry.h"

#include "ScWSettingsListEntrySetting_KeyboardInput.generated.h"

class UKeyAlreadyBoundWarning;

class UGameSetting;
class UGameSettingPressAnyKey;
class UScWButtonBase;
class UScWSettingKeyboardInput;
class UObject;

/**
 *	Settings list entry for rebinding primary/secondary keyboard keys with duplicate-key warnings.
 */
UCLASS(MinimalAPI, Abstract, Blueprintable, meta = (Category = "Settings", DisableNativeTick, DisplayName = "[ScW] Settings Keyboard Input Entry"))
class UScWSettingsListEntrySetting_KeyboardInput : public UGameSettingListEntry_Setting
{
	GENERATED_BODY()

//~ Begin Setting
public:
	virtual void SetSetting(UGameSetting* InSetting) override; // UGameSettingListEntry_Setting
protected:
	virtual void NativeOnInitialized() override; // UUserWidget
	virtual void NativeOnEntryReleased() override; // UUserWidget
	virtual void OnSettingChanged() override; // UGameSettingListEntry_Setting

	void Refresh();
//~ End Setting

//~ Begin Key Binding
protected:
	void HandlePrimaryKeyClicked();
	void HandleSecondaryKeyClicked();
	void HandleClearClicked();
	void HandleResetToDefaultClicked();

	void HandlePrimaryKeySelected(FKey InKey, UGameSettingPressAnyKey* PressAnyKeyPanel);
	void HandleSecondaryKeySelected(FKey InKey, UGameSettingPressAnyKey* PressAnyKeyPanel);
	void HandlePrimaryDuplicateKeySelected(FKey InKey, UKeyAlreadyBoundWarning* DuplicateKeyPressAnyKeyPanel) const;
	void HandleSecondaryDuplicateKeySelected(FKey InKey, UKeyAlreadyBoundWarning* DuplicateKeyPressAnyKeyPanel) const;
	void ChangeBinding(int32 BindSlot, FKey InKey);
	void HandleKeySelectionCanceled(UGameSettingPressAnyKey* PressAnyKeyPanel);
	void HandleKeySelectionCanceled(UKeyAlreadyBoundWarning* PressAnyKeyPanel);

private:
	UPROPERTY(Transient)
	FKey OriginalKeyToBind = EKeys::Invalid;

protected:
	UPROPERTY()
	TObjectPtr<UScWSettingKeyboardInput> KeyboardInputSetting;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameSettingPressAnyKey> PressAnyKeyPanelClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UKeyAlreadyBoundWarning> KeyAlreadyBoundWarningPanelClass;
//~ End Key Binding

//~ Begin Bound Widgets
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UScWButtonBase> Button_PrimaryKey;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UScWButtonBase> Button_SecondaryKey;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UScWButtonBase> Button_Clear;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UScWButtonBase> Button_ResetToDefault;
//~ End Bound Widgets
};
