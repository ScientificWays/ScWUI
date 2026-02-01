// Scientific Ways

#include "ScWUIFunctionLibrary.h"

#include "Game/ScWGameUIPolicy.h"
#include "Game/ScWPrimaryGameLayout.h"
#include "Game/ScWGameUIManagerSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWUIFunctionLibrary)

int32 UScWUIFunctionLibrary::InputSuspensions = 0;

ECommonInputType UScWUIFunctionLibrary::GetOwningPlayerInputType(const UUserWidget* InContextWidget)
{
	if (InContextWidget)
	{
		if (const UCommonInputSubsystem* InputSubsystem = UCommonInputSubsystem::Get(InContextWidget->GetOwningLocalPlayer()))
		{
			return InputSubsystem->GetCurrentInputType();
		}
	}
	return ECommonInputType::Count;
}

bool UScWUIFunctionLibrary::IsOwningPlayerUsingTouch(const UUserWidget* InContextWidget)
{
	return GetOwningPlayerInputType(InContextWidget) == ECommonInputType::Touch;
}

bool UScWUIFunctionLibrary::IsOwningPlayerUsingGamepad(const UUserWidget* InContextWidget)
{
	return GetOwningPlayerInputType(InContextWidget) == ECommonInputType::Gamepad;
}

UCommonActivatableWidget* UScWUIFunctionLibrary::PushContentToLayer_ForPlayer(const ULocalPlayer* InLocalPlayer, FGameplayTag LayerName, TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	if (!ensure(InLocalPlayer) || !ensure(WidgetClass != nullptr))
	{
		return nullptr;
	}

	if (UScWGameUIManagerSubsystem* UIManager = InLocalPlayer->GetGameInstance()->GetSubsystem<UScWGameUIManagerSubsystem>())
	{
		if (UScWGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
		{
			if (UScWPrimaryGameLayout* RootLayout = Policy->GetRootLayout(CastChecked<ULocalPlayer>(InLocalPlayer)))
			{
				return RootLayout->PushWidgetToLayerStack(LayerName, WidgetClass);
			}
		}
	}

	return nullptr;
}

void UScWUIFunctionLibrary::PushStreamedContentToLayer_ForPlayer(const ULocalPlayer* InLocalPlayer, FGameplayTag LayerName, TSoftClassPtr<UCommonActivatableWidget> WidgetClass)
{
	if (!ensure(InLocalPlayer) || !ensure(!WidgetClass.IsNull()))
	{
		return;
	}

	if (UScWGameUIManagerSubsystem* UIManager = InLocalPlayer->GetGameInstance()->GetSubsystem<UScWGameUIManagerSubsystem>())
	{
		if (UScWGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
		{
			if (UScWPrimaryGameLayout* RootLayout = Policy->GetRootLayout(CastChecked<ULocalPlayer>(InLocalPlayer)))
			{
				const bool bSuspendInputUntilComplete = true;
				RootLayout->PushWidgetToLayerStackAsync(LayerName, bSuspendInputUntilComplete, WidgetClass);
			}
		}
	}
}

void UScWUIFunctionLibrary::PopContentFromLayer(UCommonActivatableWidget* ActivatableWidget)
{
	if (!ActivatableWidget)
	{
		// Ignore request to pop an already deleted widget
		return;
	}

	if (const ULocalPlayer* InLocalPlayer = ActivatableWidget->GetOwningLocalPlayer())
	{
		if (const UScWGameUIManagerSubsystem* UIManager = InLocalPlayer->GetGameInstance()->GetSubsystem<UScWGameUIManagerSubsystem>())
		{
			if (const UScWGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
			{
				if (UScWPrimaryGameLayout* RootLayout = Policy->GetRootLayout(CastChecked<ULocalPlayer>(InLocalPlayer)))
				{
					RootLayout->FindAndRemoveWidgetFromLayer(ActivatableWidget);
				}
			}
		}
	}
}

ULocalPlayer* UScWUIFunctionLibrary::GetLocalPlayerFromController(APlayerController* InPlayerController)
{
	return InPlayerController ? InPlayerController->GetLocalPlayer() : nullptr;
}

FName UScWUIFunctionLibrary::SuspendInputForPlayer(APlayerController* InPlayerController, FName InSuspendReason)
{
	return SuspendInputForPlayer(InPlayerController ? InPlayerController->GetLocalPlayer() : nullptr, InSuspendReason);
}

FName UScWUIFunctionLibrary::SuspendInputForPlayer(ULocalPlayer* InLocalPlayer, FName InSuspendReason)
{
	if (UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(InLocalPlayer))
	{
		InputSuspensions++;
		FName SuspendToken = InSuspendReason;
		SuspendToken.SetNumber(InputSuspensions);

		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::MouseAndKeyboard, SuspendToken, true);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Gamepad, SuspendToken, true);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Touch, SuspendToken, true);

		return SuspendToken;
	}
	return NAME_None;
}

void UScWUIFunctionLibrary::ResumeInputForPlayer(APlayerController* InPlayerController, FName InSuspendToken)
{
	ResumeInputForPlayer(InPlayerController ? InPlayerController->GetLocalPlayer() : nullptr, InSuspendToken);
}

void UScWUIFunctionLibrary::ResumeInputForPlayer(ULocalPlayer* InLocalPlayer, FName InSuspendToken)
{
	if (InSuspendToken == NAME_None)
	{
		return;
	}
	if (UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(InLocalPlayer))
	{
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::MouseAndKeyboard, InSuspendToken, false);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Gamepad, InSuspendToken, false);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Touch, InSuspendToken, false);
	}
}
