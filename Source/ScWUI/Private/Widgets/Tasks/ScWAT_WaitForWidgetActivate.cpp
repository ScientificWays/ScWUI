// Scientific Ways

#include "Widgets/Tasks/ScWAT_WaitForWidgetActivate.h"

/////////////////////////////////////////////////
///////// UScWAT_WaitForWidgetActivate
/////////////////////////////////////////////////
UScWAT_WaitForWidgetActivate* UScWAT_WaitForWidgetActivate::WaitForWidgetActivate(UCommonActivatableWidget* InWidget, const bool bInTriggerOnce)
{
	ensureReturn(InWidget, nullptr);

	ThisClass* Task = NewObject<ThisClass>();
	Task->TargetWidget = InWidget;
	Task->bTriggerOnce = bInTriggerOnce;
	return Task;
}

void UScWAT_WaitForWidgetActivate::Activate() // UBlueprintAsyncActionBase
{
	Super::Activate();

	if (TargetWidget.IsValid())
	{
		TargetWidget->OnActivated().AddUObject(this, &ThisClass::HandleOnWidgetActivated);
	}
	else
	{
		Cancel();
	}
}

void UScWAT_WaitForWidgetActivate::Cancel() // UCancellableAsyncAction
{
	if (TargetWidget.IsValid())
	{
		TargetWidget->OnActivated().RemoveAll(this);
	}
	SetReadyToDestroy();
}

void UScWAT_WaitForWidgetActivate::HandleOnWidgetActivated()
{
	OnActivated.Broadcast();

	if (bTriggerOnce)
	{
		SetReadyToDestroy();
	}
}

/////////////////////////////////////////////////
///////// UScWAT_WaitForWidgetDeactivate
/////////////////////////////////////////////////
UScWAT_WaitForWidgetDeactivate* UScWAT_WaitForWidgetDeactivate::WaitForWidgetDeactivate(UCommonActivatableWidget* InWidget, const bool bInTriggerOnce)
{
	ensureReturn(InWidget, nullptr);

	ThisClass* Task = NewObject<ThisClass>();
	Task->TargetWidget = InWidget;
	Task->bTriggerOnce = bInTriggerOnce;
	return Task;
}

void UScWAT_WaitForWidgetDeactivate::Activate() // UBlueprintAsyncActionBase
{
	Super::Activate();

	if (TargetWidget.IsValid())
	{
		TargetWidget->OnDeactivated().AddUObject(this, &ThisClass::HandleOnWidgetDeactivated);
	}
	else
	{
		Cancel();
	}
}

void UScWAT_WaitForWidgetDeactivate::Cancel() // UCancellableAsyncAction
{
	if (TargetWidget.IsValid())
	{
		TargetWidget->OnDeactivated().RemoveAll(this);
	}
	SetReadyToDestroy();
}

void UScWAT_WaitForWidgetDeactivate::HandleOnWidgetDeactivated()
{
	OnDeactivated.Broadcast();

	if (bTriggerOnce)
	{
		SetReadyToDestroy();
	}
}
