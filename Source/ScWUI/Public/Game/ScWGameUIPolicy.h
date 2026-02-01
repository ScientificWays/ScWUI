// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "ScWGameUIPolicy.generated.h"

/**
 * 
 */
UENUM()
enum class ELocalMultiplayerInteractionMode : uint8
{
	// Fullscreen viewport for the primary player only, regardless of the other player's existence
	PrimaryOnly,

	// Fullscreen viewport for one player, but players can swap control over who's is displayed and who's is dormant
	SingleToggle,

	// Viewports displayed simultaneously for both players
	Simultaneous
};

USTRUCT()
struct FRootViewportLayoutInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(Transient)
	TObjectPtr<ULocalPlayer> InLocalPlayer = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UScWPrimaryGameLayout> RootLayout = nullptr;

	UPROPERTY(Transient)
	bool bAddedToViewport = false;

	FRootViewportLayoutInfo() {}
	FRootViewportLayoutInfo(ULocalPlayer* InLocalPlayer, UScWPrimaryGameLayout* InRootLayout, bool bIsInViewport)
		: InLocalPlayer(InLocalPlayer)
		, RootLayout(InRootLayout)
		, bAddedToViewport(bIsInViewport)
	{}

	bool operator==(const ULocalPlayer* OtherLocalPlayer) const { return InLocalPlayer == OtherLocalPlayer; }
};

UCLASS(MinimalAPI, Abstract, Blueprintable, Within = ScWGameUIManagerSubsystem)
class UScWGameUIPolicy : public UObject
{
	GENERATED_BODY()

public:
	template <typename GameUIPolicyClass = UScWGameUIPolicy>
	static GameUIPolicyClass* GetGameUIPolicyAs(const UObject* InWCO)
	{
		return Cast<GameUIPolicyClass>(GetGameUIPolicy(InWCO));
	}

	static MODULE_API UScWGameUIPolicy* GetGameUIPolicy(const UObject* InWCO);

public:
	MODULE_API virtual UWorld* GetWorld() const override;
	MODULE_API UScWGameUIManagerSubsystem* GetOwningUIManager() const;
	MODULE_API UScWPrimaryGameLayout* GetRootLayout(const ULocalPlayer* InLocalPlayer) const;

	ELocalMultiplayerInteractionMode GetLocalMultiplayerInteractionMode() const { return LocalMultiplayerInteractionMode; }

	MODULE_API void RequestPrimaryControl(UScWPrimaryGameLayout* Layout);

protected:
	MODULE_API void AddLayoutToViewport(ULocalPlayer* InLocalPlayer, UScWPrimaryGameLayout* Layout);
	MODULE_API void RemoveLayoutFromViewport(ULocalPlayer* InLocalPlayer, UScWPrimaryGameLayout* Layout);

	MODULE_API virtual void OnRootLayoutAddedToViewport(ULocalPlayer* InLocalPlayer, UScWPrimaryGameLayout* Layout);
	MODULE_API virtual void OnRootLayoutRemovedFromViewport(ULocalPlayer* InLocalPlayer, UScWPrimaryGameLayout* Layout);
	MODULE_API virtual void OnRootLayoutReleased(ULocalPlayer* InLocalPlayer, UScWPrimaryGameLayout* Layout);

	MODULE_API void CreateLayoutWidget(ULocalPlayer* InLocalPlayer);
	MODULE_API TSubclassOf<UScWPrimaryGameLayout> GetLayoutWidgetClass(ULocalPlayer* InLocalPlayer);

private:
	ELocalMultiplayerInteractionMode LocalMultiplayerInteractionMode = ELocalMultiplayerInteractionMode::PrimaryOnly;

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UScWPrimaryGameLayout> LayoutClass;

	UPROPERTY(Transient)
	TArray<FRootViewportLayoutInfo> RootViewportLayouts;

private:
	MODULE_API void NotifyPlayerAdded(ULocalPlayer* InLocalPlayer);
	MODULE_API void NotifyPlayerRemoved(ULocalPlayer* InLocalPlayer);
	MODULE_API void NotifyPlayerDestroyed(ULocalPlayer* InLocalPlayer);

	friend class UScWGameUIManagerSubsystem;
};
