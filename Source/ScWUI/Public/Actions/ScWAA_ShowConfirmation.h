// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "Kismet/BlueprintAsyncActionBase.h"

#include "ScWAA_ShowConfirmation.generated.h"

enum class EScWMessagingResult : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScWMessagingResultDelegate, EScWMessagingResult, Result);

/**
 * Allows easily triggering an async confirmation dialog in blueprints that you can then wait on the result.
 */
UCLASS()
class UScWAA_ShowConfirmation : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta = (BlueprintInternalUseOnly = "true", WorldContext = "InWCO"))
	static UScWAA_ShowConfirmation* ShowConfirmationYesNo(
		UObject* InWCO, FText Title, FText Message
	);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta = (BlueprintInternalUseOnly = "true", WorldContext = "InWCO"))
	static UScWAA_ShowConfirmation* ShowConfirmationOkCancel(
		UObject* InWCO, FText Title, FText Message
	);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta = (BlueprintInternalUseOnly = "true", WorldContext = "InWCO"))
	static UScWAA_ShowConfirmation* ShowConfirmationCustom(
		UObject* InWCO, UScWGameDialogDescriptor* Descriptor
	);

	virtual void Activate() override;

public:
	UPROPERTY(BlueprintAssignable)
	FScWMessagingResultDelegate OnResult;

private:
	void HandleConfirmationResult(EScWMessagingResult ConfirmationResult);

	UPROPERTY(Transient)
	TObjectPtr<UObject> WorldContextObject;

	UPROPERTY(Transient)
	TObjectPtr<ULocalPlayer> TargetLocalPlayer;

	UPROPERTY(Transient)
	TObjectPtr<UScWGameDialogDescriptor> Descriptor;
};
