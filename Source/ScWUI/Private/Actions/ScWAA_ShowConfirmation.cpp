// Scientific Ways

#include "Actions/ScWAA_ShowConfirmation.h"

#include "Engine/GameInstance.h"
#include "Messaging/ScWGameDialog.h"
#include "Messaging/ScWMessagingSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWAA_ShowConfirmation)

UScWAA_ShowConfirmation::UScWAA_ShowConfirmation(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UScWAA_ShowConfirmation* UScWAA_ShowConfirmation::ShowConfirmationYesNo(UObject* InWCO, FText Title, FText Message)
{
	UScWAA_ShowConfirmation* Action = NewObject<UScWAA_ShowConfirmation>();
	Action->WorldContextObject = InWCO;
	Action->Descriptor = UScWGameDialogDescriptor::CreateConfirmationYesNo(Title, Message);
	Action->RegisterWithGameInstance(InWCO);

	return Action;
}

UScWAA_ShowConfirmation* UScWAA_ShowConfirmation::ShowConfirmationOkCancel(UObject* InWCO, FText Title, FText Message)
{
	UScWAA_ShowConfirmation* Action = NewObject<UScWAA_ShowConfirmation>();
	Action->WorldContextObject = InWCO;
	Action->Descriptor = UScWGameDialogDescriptor::CreateConfirmationOkCancel(Title, Message);
	Action->RegisterWithGameInstance(InWCO);

	return Action;
}

UScWAA_ShowConfirmation* UScWAA_ShowConfirmation::ShowConfirmationCustom(UObject* InWCO, UScWGameDialogDescriptor* Descriptor)
{
	UScWAA_ShowConfirmation* Action = NewObject<UScWAA_ShowConfirmation>();
	Action->WorldContextObject = InWCO;
	Action->Descriptor = Descriptor;
	Action->RegisterWithGameInstance(InWCO);

	return Action;
}

void UScWAA_ShowConfirmation::Activate()
{
	if (WorldContextObject && !TargetLocalPlayer)
	{
		if (UUserWidget* UserWidget = Cast<UUserWidget>(WorldContextObject))
		{
			TargetLocalPlayer = UserWidget->GetOwningLocalPlayer<ULocalPlayer>();
		}
		else if (APlayerController* PC = Cast<APlayerController>(WorldContextObject))
		{
			TargetLocalPlayer = PC->GetLocalPlayer();
		}
		else if (UWorld* World = WorldContextObject->GetWorld())
		{
			if (UGameInstance* GameInstance = World->GetGameInstance<UGameInstance>())
			{
				TargetLocalPlayer = GameInstance->GetPrimaryPlayerController(false)->GetLocalPlayer();
			}
		}
	}

	if (TargetLocalPlayer)
	{
		if (UScWMessagingSubsystem* Messaging = TargetLocalPlayer->GetSubsystem<UScWMessagingSubsystem>())
		{
			FCommonMessagingResultDelegate ResultCallback = FCommonMessagingResultDelegate::CreateUObject(this, &UScWAA_ShowConfirmation::HandleConfirmationResult);
			Messaging->ShowConfirmation(Descriptor, ResultCallback);
			return;
		}
	}
	
	// If we couldn't make the confirmation, just handle an unknown result and broadcast nothing
	HandleConfirmationResult(EScWMessagingResult::Unknown);
}

void UScWAA_ShowConfirmation::HandleConfirmationResult(EScWMessagingResult ConfirmationResult)
{
	OnResult.Broadcast(ConfirmationResult);

	SetReadyToDestroy();
}


