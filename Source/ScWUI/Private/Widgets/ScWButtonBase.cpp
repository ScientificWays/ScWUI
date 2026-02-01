// Scientific Ways

#include "Widgets/ScWButtonBase.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWButtonBase)

void UScWButtonBase::NativePreConstruct() // UUserWidget
{
	Super::NativePreConstruct();

	UpdateButtonStyle();
	RefreshButtonText();
}

void UScWButtonBase::UpdateInputActionWidget() // UCommonButtonBase
{
	Super::UpdateInputActionWidget();

	UpdateButtonStyle();
	RefreshButtonText();
}

void UScWButtonBase::SetButtonText(const FText& InText) // UCommonButtonBase
{
	bOverride_ButtonText = InText.IsEmpty();
	ButtonText = InText;
	RefreshButtonText();
}

void UScWButtonBase::RefreshButtonText()
{
	if (bOverride_ButtonText || ButtonText.IsEmpty())
	{
		if (InputActionWidget)
		{
			const FText ActionDisplayText = InputActionWidget->GetDisplayText();	
			if (!ActionDisplayText.IsEmpty())
			{
				UpdateButtonText(ActionDisplayText);
				return;
			}
		}
	}
	
	UpdateButtonText(ButtonText);	
}

void UScWButtonBase::OnInputMethodChanged(ECommonInputType InCurrentInputType)
{
	Super::OnInputMethodChanged(InCurrentInputType);

	UpdateButtonStyle();
}
