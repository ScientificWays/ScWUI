// Scientific Ways

#pragma once

#include "CommonActivatableWidget.h"
#include "UIExtensionSystem.h"

#include "Features/ScWGFA_WorldActionBase.h"

#include "ScWGFA_AddWidget.generated.h"

struct FWorldContext;
struct FComponentRequestHandle;

/**
 *	Describes a widget layout to push onto a specific UI layer.
 */
USTRUCT()
struct FScWGameLayerRequest
{
	GENERATED_BODY()

	// The layout widget to spawn
	UPROPERTY(Category = "UI", EditAnywhere, meta = (AssetBundles = "Client"))
	TSoftClassPtr<UCommonActivatableWidget> LayoutClass;

	// The layer to insert the widget in
	UPROPERTY(Category = "UI", EditAnywhere, meta = (Categories = "UI.Layer"))
	FGameplayTag LayerTag;
};


/**
 *	Maps a widget class to a UI extension point tag for HUD element registration.
 */
USTRUCT()
struct FScWHUDElementEntry
{
	GENERATED_BODY()

	// The widget to spawn
	UPROPERTY(Category = "UI", EditAnywhere, meta = (AssetBundles = "Client"))
	TSoftClassPtr<UUserWidget> WidgetClass;

	// The slot ID where we should place this widget
	UPROPERTY(Category = "UI", EditAnywhere, meta = (Categories = "UI.Extension"))
	FGameplayTag ExtensionTag;
};

/**
 *	Game Feature action that pushes layout widgets to UI layers and registers HUD elements at extension points.
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
	UPROPERTY(Category = "UI", EditAnywhere, meta = (TitleProperty = "{LayerTag} -> {LayoutClass}"))
	TArray<FScWGameLayerRequest> Layout;

	// Widgets to add to the HUD
	UPROPERTY(Category = "UI", EditAnywhere, meta = (TitleProperty = "{ExtensionTag} -> {WidgetClass}"))
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
