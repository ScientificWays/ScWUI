// Scientific Ways

#include "Actions/ScWAA_CreateWidgetAsync.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "ScWUIFunctionLibrary.h"
#include "Engine/AssetManager.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "UObject/Stack.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWAA_CreateWidgetAsync)

class UUserWidget;

static const FName InputFilterReason_Template = FName(TEXT("CreatingWidgetAsync"));

UScWAA_CreateWidgetAsync::UScWAA_CreateWidgetAsync(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bSuspendInputUntilComplete(true)
{
}

UScWAA_CreateWidgetAsync* UScWAA_CreateWidgetAsync::CreateWidgetAsync(UObject* InWCO, TSoftClassPtr<UUserWidget> InUserWidgetSoftClass, APlayerController* InOwningPlayer, bool bSuspendInputUntilComplete)
{
	if (InUserWidgetSoftClass.IsNull())
	{
		FFrame::KismetExecutionMessage(TEXT("CreateWidgetAsync was passed a null UserWidgetSoftClass"), ELogVerbosity::Error);
		return nullptr;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(InWCO, EGetWorldErrorMode::LogAndReturnNull);

	UScWAA_CreateWidgetAsync* Action = NewObject<UScWAA_CreateWidgetAsync>();
	Action->UserWidgetSoftClass = InUserWidgetSoftClass;
	Action->OwningPlayer = InOwningPlayer;
	Action->World = World;
	Action->GameInstance = World->GetGameInstance();
	Action->bSuspendInputUntilComplete = bSuspendInputUntilComplete;
	Action->RegisterWithGameInstance(World);

	return Action;
}

void UScWAA_CreateWidgetAsync::Activate()
{
	SuspendInputToken = bSuspendInputUntilComplete ? UScWUIFunctionLibrary::SuspendInputForPlayer(OwningPlayer.Get(), InputFilterReason_Template) : NAME_None;

	TWeakObjectPtr<UScWAA_CreateWidgetAsync> LocalWeakThis(this);
	StreamingHandle = UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		UserWidgetSoftClass.ToSoftObjectPath(),
		FStreamableDelegate::CreateUObject(this, &ThisClass::OnWidgetLoaded),
		FStreamableManager::AsyncLoadHighPriority
	);

	// Setup a cancel delegate so that we can resume input if this handler is canceled.
	StreamingHandle->BindCancelDelegate(FStreamableDelegate::CreateWeakLambda(this,
		[this]()
		{
			UScWUIFunctionLibrary::ResumeInputForPlayer(OwningPlayer.Get(), SuspendInputToken);
		})
	);
}

void UScWAA_CreateWidgetAsync::Cancel()
{
	Super::Cancel();

	if (StreamingHandle.IsValid())
	{
		StreamingHandle->CancelHandle();
		StreamingHandle.Reset();
	}
}

void UScWAA_CreateWidgetAsync::OnWidgetLoaded()
{
	if (bSuspendInputUntilComplete)
	{
		UScWUIFunctionLibrary::ResumeInputForPlayer(OwningPlayer.Get(), SuspendInputToken);
	}

	// If the load as successful, create it, otherwise don't complete this.
	TSubclassOf<UUserWidget> UserWidgetClass = UserWidgetSoftClass.Get();
	if (UserWidgetClass)
	{
		UUserWidget* UserWidget = UWidgetBlueprintLibrary::Create(World.Get(), UserWidgetClass, OwningPlayer.Get());
		OnComplete.Broadcast(UserWidget);
	}

	StreamingHandle.Reset();

	SetReadyToDestroy();
}

