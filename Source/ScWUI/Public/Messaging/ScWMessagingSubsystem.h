// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "Subsystems/LocalPlayerSubsystem.h"

#include "ScWMessagingSubsystem.generated.h"

class FSubsystemCollectionBase;
class UScWGameDialogDescriptor;
class UObject;

/** Possible results from a dialog */
UENUM(BlueprintType)
enum class EScWMessagingResult : uint8
{
	/** The "yes" button was pressed */
	Confirmed,
	/** The "no" button was pressed */
	Declined,
	/** The "ignore/cancel" button was pressed */
	Cancelled,
	/** The dialog was explicitly killed (no user input) */
	Killed,
	Unknown UMETA(Hidden)
};

DECLARE_DELEGATE_OneParam(FCommonMessagingResultDelegate, EScWMessagingResult /* Result */);

/**
 * 
 */
UCLASS(MinimalAPI, config = Game)
class UScWMessagingSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	MODULE_API virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	MODULE_API virtual void Deinitialize() override;
	MODULE_API virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	MODULE_API virtual void ShowConfirmation(UScWGameDialogDescriptor* DialogDescriptor, FCommonMessagingResultDelegate ResultCallback = FCommonMessagingResultDelegate());
	MODULE_API virtual void ShowError(UScWGameDialogDescriptor* DialogDescriptor, FCommonMessagingResultDelegate ResultCallback = FCommonMessagingResultDelegate());
};
