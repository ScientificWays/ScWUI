// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "Utils/ScWTypes_CommonDelegates.h"

#include "Engine/CancellableAsyncAction.h"

#include "ScWAT_WaitForWidgetActivate.generated.h"

#define MODULE_API SCWUI_API

/**
 *	Async action that fires when a CommonActivatableWidget is activated, with optional single-trigger mode.
 */
UCLASS(MinimalAPI)
class UScWAT_WaitForWidgetActivate : public UCancellableAsyncAction
{
	GENERATED_BODY()

//~ Begin Public API
public:

	UPROPERTY(BlueprintAssignable)
	FDefaultEventSignature OnActivated;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static MODULE_API UScWAT_WaitForWidgetActivate* WaitForWidgetActivate(class UCommonActivatableWidget* InWidget, const bool bInTriggerOnce = false);

	virtual void Activate() override; // UBlueprintAsyncActionBase
	virtual void Cancel() override; // UCancellableAsyncAction
//~ End Public API

//~ Begin Internal
protected:

	UPROPERTY()
	TWeakObjectPtr<class UCommonActivatableWidget> TargetWidget;

	UPROPERTY()
	bool bTriggerOnce;

	void HandleOnWidgetActivated();
//~ End Internal
};

/**
 *	Async action that fires when a CommonActivatableWidget is deactivated, with optional single-trigger mode.
 */
UCLASS(MinimalAPI)
class UScWAT_WaitForWidgetDeactivate : public UCancellableAsyncAction
{
	GENERATED_BODY()

//~ Begin Public API
public:

	UPROPERTY(BlueprintAssignable)
	FDefaultEventSignature OnDeactivated;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static MODULE_API UScWAT_WaitForWidgetDeactivate* WaitForWidgetDeactivate(class UCommonActivatableWidget* InWidget, const bool bInTriggerOnce = false);

	virtual void Activate() override; // UBlueprintAsyncActionBase
	virtual void Cancel() override; // UCancellableAsyncAction
//~ End Public API

//~ Begin Internal
protected:

	UPROPERTY()
	TWeakObjectPtr<class UCommonActivatableWidget> TargetWidget;

	UPROPERTY()
	bool bTriggerOnce;

	void HandleOnWidgetDeactivated();
//~ End Internal
};

#undef MODULE_API
