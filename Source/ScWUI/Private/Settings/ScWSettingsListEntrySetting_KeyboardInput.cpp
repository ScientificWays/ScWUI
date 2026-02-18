// Scientific Ways

#include "Settings/ScWSettingsListEntrySetting_KeyboardInput.h"

#include "CommonUIExtensions.h"
#include "Settings/Customization/ScWSettingKeyboardInput.h"

#include "Tags/ScWUITags.h"

#include "Widgets/ScWButtonBase.h"
#include "Widgets/Misc/GameSettingPressAnyKey.h"
#include "Widgets/Misc/KeyAlreadyBoundWarning.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWSettingsListEntrySetting_KeyboardInput)

#define LOCTEXT_NAMESPACE "ScWSettings"

void UScWSettingsListEntrySetting_KeyboardInput::SetSetting(UGameSetting* InSetting)
{
	KeyboardInputSetting = CastChecked<UScWSettingKeyboardInput>(InSetting);

	Super::SetSetting(InSetting);

	Refresh();
}

void UScWSettingsListEntrySetting_KeyboardInput::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	Button_PrimaryKey->OnClicked().AddUObject(this, &ThisClass::HandlePrimaryKeyClicked);
	Button_SecondaryKey->OnClicked().AddUObject(this, &ThisClass::HandleSecondaryKeyClicked);
	Button_Clear->OnClicked().AddUObject(this, &ThisClass::HandleClearClicked);
	Button_ResetToDefault->OnClicked().AddUObject(this, &ThisClass::HandleResetToDefaultClicked);	
}

void UScWSettingsListEntrySetting_KeyboardInput::HandlePrimaryKeyClicked()
{
	UGameSettingPressAnyKey* PressAnyKeyPanel = CastChecked<UGameSettingPressAnyKey>(
		UCommonUIExtensions::PushContentToLayer_ForPlayer(GetOwningLocalPlayer(), FScWUITags::UI_Layer_Modal, PressAnyKeyPanelClass));
	PressAnyKeyPanel->OnKeySelected.AddUObject(this, &ThisClass::HandlePrimaryKeySelected, PressAnyKeyPanel);
	PressAnyKeyPanel->OnKeySelectionCanceled.AddUObject(this, &ThisClass::HandleKeySelectionCanceled, PressAnyKeyPanel);
}

void UScWSettingsListEntrySetting_KeyboardInput::HandleSecondaryKeyClicked()
{
	UGameSettingPressAnyKey* PressAnyKeyPanel = CastChecked<UGameSettingPressAnyKey>(
		UCommonUIExtensions::PushContentToLayer_ForPlayer(GetOwningLocalPlayer(), FScWUITags::UI_Layer_Modal, PressAnyKeyPanelClass));
	PressAnyKeyPanel->OnKeySelected.AddUObject(this, &ThisClass::HandleSecondaryKeySelected, PressAnyKeyPanel);
	PressAnyKeyPanel->OnKeySelectionCanceled.AddUObject(this, &ThisClass::HandleKeySelectionCanceled, PressAnyKeyPanel);
}

void UScWSettingsListEntrySetting_KeyboardInput::HandlePrimaryKeySelected(FKey InKey, UGameSettingPressAnyKey* PressAnyKeyPanel)
{
	PressAnyKeyPanel->OnKeySelected.RemoveAll(this);
	ChangeBinding(0, InKey);
}

void UScWSettingsListEntrySetting_KeyboardInput::HandleSecondaryKeySelected(FKey InKey, UGameSettingPressAnyKey* PressAnyKeyPanel)
{
	PressAnyKeyPanel->OnKeySelected.RemoveAll(this);
	ChangeBinding(1, InKey);
}

void UScWSettingsListEntrySetting_KeyboardInput::HandlePrimaryDuplicateKeySelected(FKey InKey, UKeyAlreadyBoundWarning* DuplicateKeyPressAnyKeyPanel) const
{
	DuplicateKeyPressAnyKeyPanel->OnKeySelected.RemoveAll(this);
	KeyboardInputSetting->ChangeBinding(0, OriginalKeyToBind);
}

void UScWSettingsListEntrySetting_KeyboardInput::HandleSecondaryDuplicateKeySelected(FKey InKey, UKeyAlreadyBoundWarning* DuplicateKeyPressAnyKeyPanel) const
{
	DuplicateKeyPressAnyKeyPanel->OnKeySelected.RemoveAll(this);
	KeyboardInputSetting->ChangeBinding(1, OriginalKeyToBind);
}

void UScWSettingsListEntrySetting_KeyboardInput::ChangeBinding(int32 InKeyBindSlot, FKey InKey)
{
	OriginalKeyToBind = InKey;
	TArray<FName> ActionsForKey;
	KeyboardInputSetting->GetAllMappedActionsFromKey(InKeyBindSlot, InKey, ActionsForKey);
	if (!ActionsForKey.IsEmpty())
	{
		UKeyAlreadyBoundWarning* KeyAlreadyBoundWarning = CastChecked<UKeyAlreadyBoundWarning>(
		UCommonUIExtensions::PushContentToLayer_ForPlayer(GetOwningLocalPlayer(), FScWUITags::UI_Layer_Modal, KeyAlreadyBoundWarningPanelClass));

		FString ActionNames;
		for (FName ActionName : ActionsForKey)
		{
			ActionNames += ActionName.ToString() += ", ";
		}

		FFormatNamedArguments Args;
		Args.Add(TEXT("InKey"), InKey.GetDisplayName());
		Args.Add(TEXT("ActionNames"), FText::FromString(ActionNames));

		KeyAlreadyBoundWarning->SetWarningText(FText::Format(LOCTEXT("WarningText", "{InKey} is already bound to {ActionNames} are you sure you want to rebind it?"), Args));
		KeyAlreadyBoundWarning->SetCancelText(FText::Format(LOCTEXT("CancelText", "Press escape to cancel, or press {InKey} again to confirm rebinding."), Args));

		if (InKeyBindSlot == 1)
		{
			KeyAlreadyBoundWarning->OnKeySelected.AddUObject(this, &ThisClass::HandleSecondaryDuplicateKeySelected, KeyAlreadyBoundWarning);
		}
		else
		{
			KeyAlreadyBoundWarning->OnKeySelected.AddUObject(this, &ThisClass::HandlePrimaryDuplicateKeySelected, KeyAlreadyBoundWarning);
		}
		KeyAlreadyBoundWarning->OnKeySelectionCanceled.AddUObject(this, &ThisClass::HandleKeySelectionCanceled, KeyAlreadyBoundWarning);
	}
	else
	{
		KeyboardInputSetting->ChangeBinding(InKeyBindSlot, InKey);
	}
}

void UScWSettingsListEntrySetting_KeyboardInput::HandleKeySelectionCanceled(UGameSettingPressAnyKey* PressAnyKeyPanel)
{
	PressAnyKeyPanel->OnKeySelectionCanceled.RemoveAll(this);
}

void UScWSettingsListEntrySetting_KeyboardInput::HandleKeySelectionCanceled(UKeyAlreadyBoundWarning* PressAnyKeyPanel)
{
	PressAnyKeyPanel->OnKeySelectionCanceled.RemoveAll(this);
}

void UScWSettingsListEntrySetting_KeyboardInput::HandleClearClicked()
{
	KeyboardInputSetting->ChangeBinding(0, EKeys::Invalid);
	KeyboardInputSetting->ChangeBinding(1, EKeys::Invalid);
}

void UScWSettingsListEntrySetting_KeyboardInput::HandleResetToDefaultClicked()
{
	KeyboardInputSetting->ResetToDefault();
}

void UScWSettingsListEntrySetting_KeyboardInput::OnSettingChanged()
{
	Refresh();
}

void UScWSettingsListEntrySetting_KeyboardInput::Refresh()
{
	if (ensure(KeyboardInputSetting))
	{
		Button_PrimaryKey->SetButtonText(KeyboardInputSetting->GetKeyTextFromSlot(EPlayerMappableKeySlot::First));
		Button_SecondaryKey->SetButtonText(KeyboardInputSetting->GetKeyTextFromSlot(EPlayerMappableKeySlot::Second));
		
		// Only display the reset to default button if a mapping is customized
		if (ensure(Button_ResetToDefault))
		{
			if (KeyboardInputSetting->IsMappingCustomized())
			{
				Button_ResetToDefault->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				Button_ResetToDefault->SetVisibility(ESlateVisibility::Hidden);
			}
		}		
	}
}

void UScWSettingsListEntrySetting_KeyboardInput::NativeOnEntryReleased()
{
	Super::NativeOnEntryReleased();

	KeyboardInputSetting = nullptr;
}

#undef LOCTEXT_NAMESPACE
