// Scientific Ways

#pragma once

#include "CommonActivatableWidget.h"
#include "UIExtensionSystem.h"

#include "Features/ScWGFA_WorldActionBase.h"

#include "ScWGFA_AddWidget.generated.h"

struct FWorldContext;
struct FComponentRequestHandle;

USTRUCT()
struct FScWHUDLayoutRequest
{
	GENERATED_BODY()

	// The layout widget to spawn
	UPROPERTY(EditAnywhere, Category=UI, meta = (AssetBundles="Client"))
	TSoftClassPtr<UCommonActivatableWidget> LayoutClass;

	// The layer to insert the widget in
	UPROPERTY(EditAnywhere, Category=UI, meta = (Categories="UI.Layer"))
	FGameplayTag LayerTag;
};


USTRUCT()
struct FScWHUDElementEntry
{
	GENERATED_BODY()

	// The widget to spawn
	UPROPERTY(EditAnywhere, Category=UI, meta = (AssetBundles="Client"))
	TSoftClassPtr<UUserWidget> WidgetClass;

	// The slot ID where we should place this widget
	UPROPERTY(EditAnywhere, Category = UI, meta = (Categories = "UI.Extension"))
	FGameplayTag ExtensionTag;
};

//////////////////////////////////////////////////////////////////////
// UScWGFA_AddWidget

/**
 * GameFeatureAction responsible for adding widgets.
 */
UCLASS(MinimalAPI, meta = (DisplayName = "Add Widgets"))
class UScWGFA_AddWidgets final : public UScWGFA_WorldActionBase
{
	GENERATED_BODY()

public:
	//~ Begin UGameFeatureAction interface
	virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;
#if WITH_EDITORONLY_DATA
	virtual void AddAdditionalAssetBundleData(FAssetBundleData& AssetBundleData) override;
#endif
	//~ End UGameFeatureAction interface

	//~ Begin UObject interface
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif
	//~ End UObject interface

private:
	// Layout to add to the HUD
	UPROPERTY(EditAnywhere, Category=UI, meta = (TitleProperty="{LayerTag} -> {LayoutClass}"))
	TArray<FScWHUDLayoutRequest> Layout;

	// Widgets to add to the HUD
	UPROPERTY(EditAnywhere, Category=UI, meta = (TitleProperty="{ExtensionTag} -> {WidgetClass}"))
	TArray<FScWHUDElementEntry> Widgets;

private:

	struct FPerActorData
	{
		TArray<TWeakObjectPtr<UCommonActivatableWidget>> LayoutsAdded;
		TArray<FUIExtensionHandle> ExtensionHandles;
	};

	struct FPerContextData
	{
		TArray<TSharedPtr<FComponentRequestHandle>> ComponentRequests;
		TMap<FObjectKey, FPerActorData> ActorData; 
	};

	TMap<FGameFeatureStateChangeContext, FPerContextData> ContextData;

	//~ Begin UScWGFA_WorldActionBase interface
	virtual void AddToWorld(const FWorldContext& WorldContext, const FGameFeatureStateChangeContext& ChangeContext) override;
	//~ End UScWGFA_WorldActionBase interface

	void Reset(FPerContextData& ActiveData);

	void HandleActorExtension(AActor* Actor, FName EventName, FGameFeatureStateChangeContext ChangeContext);

	void AddWidgets(AActor* Actor, FPerContextData& ActiveData);
	void RemoveWidgets(AActor* Actor, FPerContextData& ActiveData);
};
