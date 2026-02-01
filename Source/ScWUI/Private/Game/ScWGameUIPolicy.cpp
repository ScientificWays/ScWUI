// Scientific Ways

#include "Game/ScWGameUIPolicy.h"

#include "Game/ScWPrimaryGameLayout.h"
#include "Game/ScWGameUIManagerSubsystem.h"

#include "ScWUILogChannels.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWGameUIPolicy)

// Static
UScWGameUIPolicy* UScWGameUIPolicy::GetGameUIPolicy(const UObject* InWCO)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(InWCO, EGetWorldErrorMode::LogAndReturnNull))
	{
		if (UGameInstance* GameInstance = World->GetGameInstance())
		{
			if (UScWGameUIManagerSubsystem* UIManager = UGameInstance::GetSubsystem<UScWGameUIManagerSubsystem>(GameInstance))
			{
				return UIManager->GetCurrentUIPolicy();
			}
		}
	}

	return nullptr;
}

UScWGameUIManagerSubsystem* UScWGameUIPolicy::GetOwningUIManager() const
{
	return CastChecked<UScWGameUIManagerSubsystem>(GetOuter());
}

UWorld* UScWGameUIPolicy::GetWorld() const
{
	return GetOwningUIManager()->GetGameInstance()->GetWorld();
}

UScWPrimaryGameLayout* UScWGameUIPolicy::GetRootLayout(const ULocalPlayer* InLocalPlayer) const
{
	const FRootViewportLayoutInfo* LayoutInfo = RootViewportLayouts.FindByKey(InLocalPlayer);
	return LayoutInfo ? LayoutInfo->RootLayout : nullptr;
}

void UScWGameUIPolicy::NotifyPlayerAdded(ULocalPlayer* InLocalPlayer)
{
	InLocalPlayer->OnPlayerControllerChanged().AddWeakLambda(this, [this](APlayerController* InPlayerController)
	{
		auto InLocalPlayer = InPlayerController->GetLocalPlayer();
		NotifyPlayerRemoved(InLocalPlayer);

		if (FRootViewportLayoutInfo* LayoutInfo = RootViewportLayouts.FindByKey(InLocalPlayer))
		{
			AddLayoutToViewport(InLocalPlayer, LayoutInfo->RootLayout);
			LayoutInfo->bAddedToViewport = true;
		}
		else
		{
			CreateLayoutWidget(InLocalPlayer);
		}
	});
	if (FRootViewportLayoutInfo* LayoutInfo = RootViewportLayouts.FindByKey(InLocalPlayer))
	{
		AddLayoutToViewport(InLocalPlayer, LayoutInfo->RootLayout);
		LayoutInfo->bAddedToViewport = true;
	}
	else
	{
		CreateLayoutWidget(InLocalPlayer);
	}
}

void UScWGameUIPolicy::NotifyPlayerRemoved(ULocalPlayer* InLocalPlayer)
{
	if (FRootViewportLayoutInfo* LayoutInfo = RootViewportLayouts.FindByKey(InLocalPlayer))
	{
		RemoveLayoutFromViewport(InLocalPlayer, LayoutInfo->RootLayout);
		LayoutInfo->bAddedToViewport = false;

		if (LocalMultiplayerInteractionMode == ELocalMultiplayerInteractionMode::SingleToggle && !InLocalPlayer->IsPrimaryPlayer())
		{
			UScWPrimaryGameLayout* RootLayout = LayoutInfo->RootLayout;
			if (RootLayout && !RootLayout->IsDormant())
			{
				// We're removing a secondary player's root while it's in control - transfer control back to the primary player's root
				RootLayout->SetIsDormant(true);
				for (const FRootViewportLayoutInfo& RootLayoutInfo : RootViewportLayouts)
				{
					if (RootLayoutInfo.InLocalPlayer->IsPrimaryPlayer())
					{
						if (UScWPrimaryGameLayout* PrimaryRootLayout = RootLayoutInfo.RootLayout)
						{
							PrimaryRootLayout->SetIsDormant(false);
						}
					}
				}
			}
		}
	}
}

void UScWGameUIPolicy::NotifyPlayerDestroyed(ULocalPlayer* InLocalPlayer)
{
	NotifyPlayerRemoved(InLocalPlayer);
	InLocalPlayer->OnPlayerControllerChanged().RemoveAll(this);

	const int32 LayoutInfoIdx = RootViewportLayouts.IndexOfByKey(InLocalPlayer);
	if (LayoutInfoIdx != INDEX_NONE)
	{
		UScWPrimaryGameLayout* Layout = RootViewportLayouts[LayoutInfoIdx].RootLayout;
		RootViewportLayouts.RemoveAt(LayoutInfoIdx);

		RemoveLayoutFromViewport(InLocalPlayer, Layout);

		OnRootLayoutReleased(InLocalPlayer, Layout);
	}
}

void UScWGameUIPolicy::AddLayoutToViewport(ULocalPlayer* InLocalPlayer, UScWPrimaryGameLayout* Layout)
{
	UE_LOG(LogScWUI, Log, TEXT("[%s] is adding player [%s]'s root layout [%s] to the viewport"), *GetName(), *GetNameSafe(InLocalPlayer), *GetNameSafe(Layout));

	Layout->SetPlayerContext(FLocalPlayerContext(InLocalPlayer));
	Layout->AddToPlayerScreen(1000);

	OnRootLayoutAddedToViewport(InLocalPlayer, Layout);
}

void UScWGameUIPolicy::RemoveLayoutFromViewport(ULocalPlayer* InLocalPlayer, UScWPrimaryGameLayout* Layout)
{
	TWeakPtr<SWidget> LayoutSlateWidget = Layout->GetCachedWidget();
	if (LayoutSlateWidget.IsValid())
	{
		UE_LOG(LogScWUI, Log, TEXT("[%s] is removing player [%s]'s root layout [%s] from the viewport"), *GetName(), *GetNameSafe(InLocalPlayer), *GetNameSafe(Layout));

		Layout->RemoveFromParent();
		if (LayoutSlateWidget.IsValid())
		{
			UE_LOG(LogScWUI, Log, TEXT("Player [%s]'s root layout [%s] has been removed from the viewport, but other references to its underlying Slate widget still exist. Noting in case we leak it."), *GetNameSafe(InLocalPlayer), *GetNameSafe(Layout));
		}

		OnRootLayoutRemovedFromViewport(InLocalPlayer, Layout);
	}
}

void UScWGameUIPolicy::OnRootLayoutAddedToViewport(ULocalPlayer* InLocalPlayer, UScWPrimaryGameLayout* Layout)
{
#if WITH_EDITOR
	if (GIsEditor && InLocalPlayer->IsPrimaryPlayer())
	{
		// So our controller will work in PIE without needing to click in the viewport
		FSlateApplication::Get().SetUserFocusToGameViewport(0);
	}
#endif
}

void UScWGameUIPolicy::OnRootLayoutRemovedFromViewport(ULocalPlayer* InLocalPlayer, UScWPrimaryGameLayout* Layout)
{
	
}

void UScWGameUIPolicy::OnRootLayoutReleased(ULocalPlayer* InLocalPlayer, UScWPrimaryGameLayout* Layout)
{
	
}

void UScWGameUIPolicy::RequestPrimaryControl(UScWPrimaryGameLayout* Layout)
{
	if (LocalMultiplayerInteractionMode == ELocalMultiplayerInteractionMode::SingleToggle && Layout->IsDormant())
	{
		for (const FRootViewportLayoutInfo& LayoutInfo : RootViewportLayouts)
		{
			UScWPrimaryGameLayout* RootLayout = LayoutInfo.RootLayout;
			if (RootLayout && !RootLayout->IsDormant())
			{
				RootLayout->SetIsDormant(true);
				break;
			}
		}
		Layout->SetIsDormant(false);
	}
}

void UScWGameUIPolicy::CreateLayoutWidget(ULocalPlayer* InLocalPlayer)
{
	if (APlayerController* PlayerController = InLocalPlayer->GetPlayerController(GetWorld()))
	{
		TSubclassOf<UScWPrimaryGameLayout> LayoutWidgetClass = GetLayoutWidgetClass(InLocalPlayer);
		if (ensure(LayoutWidgetClass && !LayoutWidgetClass->HasAnyClassFlags(CLASS_Abstract)))
		{
			UScWPrimaryGameLayout* NewLayoutObject = CreateWidget<UScWPrimaryGameLayout>(PlayerController, LayoutWidgetClass);
			RootViewportLayouts.Emplace(InLocalPlayer, NewLayoutObject, true);
			
			AddLayoutToViewport(InLocalPlayer, NewLayoutObject);
		}
	}
}

TSubclassOf<UScWPrimaryGameLayout> UScWGameUIPolicy::GetLayoutWidgetClass(ULocalPlayer* InLocalPlayer)
{
	return LayoutClass.LoadSynchronous();
}
