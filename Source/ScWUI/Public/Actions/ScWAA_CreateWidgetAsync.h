// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "Engine/CancellableAsyncAction.h"

#include "ScWAA_CreateWidgetAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScWCreateWidgetAsyncDelegate, UUserWidget*, InUserWidget);

/**
 * Load the widget class asynchronously, the instance the widget after the loading completes, and return it on OnComplete.
 */
UCLASS(MinimalAPI, BlueprintType)
class UScWAA_CreateWidgetAsync : public UCancellableAsyncAction
{
	GENERATED_UCLASS_BODY()

public:
	MODULE_API virtual void Cancel() override;

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta=(WorldContext = "WorldContextObject", BlueprintInternalUseOnly="true"))
	static MODULE_API UScWAA_CreateWidgetAsync* CreateWidgetAsync(UObject* WorldContextObject, TSoftClassPtr<UUserWidget> UserWidgetSoftClass, APlayerController* OwningPlayer, bool bSuspendInputUntilComplete = true);

	MODULE_API virtual void Activate() override;

public:

	UPROPERTY(BlueprintAssignable)
	FScWCreateWidgetAsyncDelegate OnComplete;

private:
	
	void OnWidgetLoaded();

	FName SuspendInputToken;
	TWeakObjectPtr<APlayerController> OwningPlayer;
	TWeakObjectPtr<UWorld> World;
	TWeakObjectPtr<UGameInstance> GameInstance;
	bool bSuspendInputUntilComplete;
	TSoftClassPtr<UUserWidget> UserWidgetSoftClass;
	TSharedPtr<FStreamableHandle> StreamingHandle;
};
