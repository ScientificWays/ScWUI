// Scientific Ways

#include "Game/ScWGameUIManagerSubsystem.h"

#include "Game/ScWGameUIPolicy.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWGameUIManagerSubsystem)

UScWGameUIManagerSubsystem::UScWGameUIManagerSubsystem()
{

}

void UScWGameUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (!CurrentPolicy && !DefaultUIPolicyClass.IsNull())
	{
		TSubclassOf<UScWGameUIPolicy> PolicyClass = DefaultUIPolicyClass.LoadSynchronous();
		SwitchToPolicy(NewObject<UScWGameUIPolicy>(this, PolicyClass));
	}
}

void UScWGameUIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();

	SwitchToPolicy(nullptr);
}

bool UScWGameUIManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> ChildClasses;
		GetDerivedClasses(GetClass(), ChildClasses, false);

		// Only create an instance if there is no override implementation defined elsewhere
		return ChildClasses.Num() == 0;
	}

	return false;
}

void UScWGameUIManagerSubsystem::NotifyPlayerAdded(ULocalPlayer* InLocalPlayer)
{
	if (ensure(InLocalPlayer) && CurrentPolicy)
	{
		CurrentPolicy->NotifyPlayerAdded(InLocalPlayer);
	}
}

void UScWGameUIManagerSubsystem::NotifyPlayerRemoved(ULocalPlayer* InLocalPlayer)
{
	if (InLocalPlayer && CurrentPolicy)
	{
		CurrentPolicy->NotifyPlayerRemoved(InLocalPlayer);
	}
}

void UScWGameUIManagerSubsystem::NotifyPlayerDestroyed(ULocalPlayer* InLocalPlayer)
{
	if (InLocalPlayer && CurrentPolicy)
	{
		CurrentPolicy->NotifyPlayerDestroyed(InLocalPlayer);
	}
}

void UScWGameUIManagerSubsystem::SwitchToPolicy(UScWGameUIPolicy* InPolicy)
{
	if (CurrentPolicy != InPolicy)
	{
		CurrentPolicy = InPolicy;
	}
}

