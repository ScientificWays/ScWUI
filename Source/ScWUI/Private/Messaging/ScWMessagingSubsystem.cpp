// Scientific Ways

#include "Messaging/ScWMessagingSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWMessagingSubsystem)

class FSubsystemCollectionBase;
class UClass;

void UScWMessagingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UScWMessagingSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool UScWMessagingSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	UGameInstance* GameInstance = CastChecked<ULocalPlayer>(Outer)->GetGameInstance();
	if (GameInstance && !GameInstance->IsDedicatedServerInstance())
	{
		TArray<UClass*> ChildClasses;
		GetDerivedClasses(GetClass(), ChildClasses, false);

		// Only create an instance if there is no override implementation defined elsewhere
		return ChildClasses.Num() == 0;
	}

	return false;
}

void UScWMessagingSubsystem::ShowConfirmation(UScWGameDialogDescriptor* DialogDescriptor, FCommonMessagingResultDelegate ResultCallback)
{
	
}

void UScWMessagingSubsystem::ShowError(UScWGameDialogDescriptor* DialogDescriptor, FCommonMessagingResultDelegate ResultCallback)
{
	
}
