// Scientific Ways

#pragma once

#include "Features/ScWGFA_WorldActionBase.h"
#include "UObject/ObjectKey.h"

#include "ScWGFA_SplitscreenConfig.generated.h"

#define MODULE_API SCWUI_API

class UObject;
struct FGameFeatureDeactivatingContext;
struct FGameFeatureStateChangeContext;
struct FWorldContext;

/**
 *	Game Feature action that enables or disables splitscreen via a global voting system.
 */
UCLASS(MinimalAPI, meta = (DisplayName = "Splitscreen Config"))
class UScWGFA_SplitscreenConfig final : public UScWGFA_WorldActionBase
{
	GENERATED_BODY()

public:
	//~ Begin UGameFeatureAction interface
	virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;
	//~ End UGameFeatureAction interface

	//~ Begin UScWGFA_WorldActionBase interface
	virtual void AddToWorld(const FWorldContext& WorldContext, const FGameFeatureStateChangeContext& ChangeContext) override;
	//~ End UScWGFA_WorldActionBase interface

public:
	UPROPERTY(Category = "Action", EditAnywhere)
	bool bDisableSplitscreen = true;

private:
	TArray<FObjectKey> LocalDisableVotes;

	static TMap<FObjectKey, int32> GlobalDisableVotes;
};

#undef MODULE_API
