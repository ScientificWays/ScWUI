// Scientific Ways

#include "Game/ScWPrimaryGameLayout.h"

#include "Game/ScWGameUIPolicy.h"
#include "Game/ScWGameUIManagerSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWPrimaryGameLayout)

class UObject;

/*static*/ UScWPrimaryGameLayout* UScWPrimaryGameLayout::GetPrimaryGameLayoutForPrimaryPlayer(const UObject* InWCO)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(InWCO);
	APlayerController* PlayerController = GameInstance->GetPrimaryPlayerController(false);
	return GetPrimaryGameLayout(PlayerController);
}

/*static*/ UScWPrimaryGameLayout* UScWPrimaryGameLayout::GetPrimaryGameLayout(APlayerController* InPlayerController)
{
	return InPlayerController ? GetPrimaryGameLayout(Cast<ULocalPlayer>(InPlayerController->Player)) : nullptr;
}

/*static*/ UScWPrimaryGameLayout* UScWPrimaryGameLayout::GetPrimaryGameLayout(ULocalPlayer* InLocalPlayer)
{
	if (InLocalPlayer)
	{
		if (const UGameInstance* GameInstance = InLocalPlayer->GetGameInstance())
		{
			if (UScWGameUIManagerSubsystem* UIManager = GameInstance->GetSubsystem<UScWGameUIManagerSubsystem>())
			{
				if (const UScWGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
				{
					if (UScWPrimaryGameLayout* RootLayout = Policy->GetRootLayout(InLocalPlayer))
					{
						return RootLayout;
					}
				}
			}
		}
	}
	return nullptr;
}

UScWPrimaryGameLayout::UScWPrimaryGameLayout(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UScWPrimaryGameLayout::SetIsDormant(bool InDormant)
{
	if (bIsDormant != InDormant)
	{
		const ULocalPlayer* LP = GetOwningLocalPlayer();
		const int32 PlayerId = LP ? LP->GetControllerId() : -1;
		const TCHAR* OldDormancyStr = bIsDormant ? TEXT("Dormant") : TEXT("Not-Dormant");
		const TCHAR* NewDormancyStr = InDormant ? TEXT("Dormant") : TEXT("Not-Dormant");
		const TCHAR* PrimaryPlayerStr = LP && LP->IsPrimaryPlayer() ? TEXT("[Primary]") : TEXT("[Non-Primary]");
		UE_LOG(LogScWUI, Display, TEXT("%s PrimaryGameLayout Dormancy changed for [%d] from [%s] to [%s]"), PrimaryPlayerStr, PlayerId, OldDormancyStr, NewDormancyStr);

		bIsDormant = InDormant;
		OnIsDormantChanged();
	}
}

void UScWPrimaryGameLayout::OnIsDormantChanged()
{
	//@TODO NDarnell Determine what to do with dormancy, in the past we treated dormancy as a way to shutoff rendering
	//and the view for the other local players when we force multiple players to use the player view of a single player.
	
	//if (ULocalPlayer* InLocalPlayer = GetOwningLocalPlayer<ULocalPlayer>())
	//{
	//	// When the root layout is dormant, we don't want to render anything from the owner's view either
	//	InLocalPlayer->SetIsPlayerViewEnabled(!bIsDormant);
	//}

	//SetVisibility(bIsDormant ? ESlateVisibility::Collapsed : ESlateVisibility::SelfHitTestInvisible);

	//OnLayoutDormancyChanged().Broadcast(bIsDormant);
}

void UScWPrimaryGameLayout::RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* LayerWidget)
{
	if (!IsDesignTime())
	{
		LayerWidget->OnTransitioningChanged.AddUObject(this, &UScWPrimaryGameLayout::OnWidgetStackTransitioning);
		// TODO: Consider allowing a transition duration, we currently set it to 0, because if it's not 0, the
		//       transition effect will cause focus to not transition properly to the new widgets when using
		//       gamepad always.
		LayerWidget->SetTransitionDuration(0.0);

		Layers.Add(LayerTag, LayerWidget);
	}
}

void UScWPrimaryGameLayout::OnWidgetStackTransitioning(UCommonActivatableWidgetContainerBase* Widget, bool bIsTransitioning)
{
	if (bIsTransitioning)
	{
		const FName SuspendToken = UScWUIFunctionLibrary::SuspendInputForPlayer(GetOwningLocalPlayer(), TEXT("GlobalStackTransion"));
		SuspendInputTokens.Add(SuspendToken);
	}
	else
	{
		if (ensure(SuspendInputTokens.Num() > 0))
		{
			const FName SuspendToken = SuspendInputTokens.Pop();
			UScWUIFunctionLibrary::ResumeInputForPlayer(GetOwningLocalPlayer(), SuspendToken);
		}
	}
}

void UScWPrimaryGameLayout::FindAndRemoveWidgetFromLayer(UCommonActivatableWidget* ActivatableWidget)
{
	// We're not sure what layer the widget is on so go searching.
	for (const auto& LayerKVP : Layers)
	{
		LayerKVP.Value->RemoveWidget(*ActivatableWidget);
	}
}

UCommonActivatableWidgetContainerBase* UScWPrimaryGameLayout::GetLayerWidget(FGameplayTag LayerName)
{
	return Layers.FindRef(LayerName);
}
