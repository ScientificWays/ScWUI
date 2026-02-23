// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "Utils/ScWTypes_CommonDelegates.h"

#include "Engine/CancellableAsyncAction.h"

#include "ScWAT_WaitForWidgetActivate.generated.h"

#define MODULE_API SCWUI_API

/**
 *	
 */
UCLASS(MinimalAPI)
class UScWAT_WaitForWidgetActivate : public UCancellableAsyncAction
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FDefaultEventSignature OnActivated;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static MODULE_API UScWAT_WaitForWidgetActivate* WaitForWidgetActivate(class UCommonActivatableWidget* InWidget, const bool bInTriggerOnce = false);

	virtual void Activate() override; // UBlueprintAsyncActionBase
	virtual void Cancel() override; // UCancellableAsyncAction
protected:

	UPROPERTY()
	TWeakObjectPtr<class UCommonActivatableWidget> TargetWidget;

	UPROPERTY()
	bool bTriggerOnce;

	void HandleOnWidgetActivated();
};

/**
 *
 */
UCLASS(MinimalAPI)
class UScWAT_WaitForWidgetDeactivate : public UCancellableAsyncAction
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FDefaultEventSignature OnDeactivated;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static MODULE_API UScWAT_WaitForWidgetDeactivate* WaitForWidgetDeactivate(class UCommonActivatableWidget* InWidget, const bool bInTriggerOnce = false);

	virtual void Activate() override; // UBlueprintAsyncActionBase
	virtual void Cancel() override; // UCancellableAsyncAction
protected:

	UPROPERTY()
	TWeakObjectPtr<class UCommonActivatableWidget> TargetWidget;

	UPROPERTY()
	bool bTriggerOnce;

	void HandleOnWidgetDeactivated();
};

#undef MODULE_API
