// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "Subsystems/GameInstanceSubsystem.h"

#include "ScWGameUIManagerSubsystem.generated.h"

/**
 * This manager is intended to be replaced by whatever your game needs to
 * actually create, so this class is abstract to prevent it from being created.
 * 
 * If you just need the basic functionality you will start by sublcassing this
 * subsystem in your own game.
 */
UCLASS(MinimalAPI, Abstract, config = Game)
class UScWGameUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UScWGameUIManagerSubsystem();
	
	MODULE_API virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	MODULE_API virtual void Deinitialize() override;
	MODULE_API virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
	const class UScWGameUIPolicy* GetCurrentUIPolicy() const { return CurrentPolicy; }
	class UScWGameUIPolicy* GetCurrentUIPolicy() { return CurrentPolicy; }

	MODULE_API virtual void NotifyPlayerAdded(ULocalPlayer* InLocalPlayer);
	MODULE_API virtual void NotifyPlayerRemoved(ULocalPlayer* InLocalPlayer);
	MODULE_API virtual void NotifyPlayerDestroyed(ULocalPlayer* InLocalPlayer);

protected:
	MODULE_API void SwitchToPolicy(class UScWGameUIPolicy* InPolicy);

private:
	UPROPERTY(Transient)
	TObjectPtr<class UScWGameUIPolicy> CurrentPolicy = nullptr;

	UPROPERTY(config, EditAnywhere)
	TSoftClassPtr<class UScWGameUIPolicy> DefaultUIPolicyClass;
};
