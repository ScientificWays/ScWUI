// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "Subsystems/GameInstanceSubsystem.h"

#include "ScWLoadingScreenSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScWLoadingScreenWidgetChangedDelegate, TSubclassOf<UUserWidget>, InNewWidgetClass);

/**
 * Tracks/stores the current loading screen configuration in a place
 * that persists across map transitions
 */
UCLASS(MinimalAPI)
class UScWLoadingScreenSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UScWLoadingScreenSubsystem();

	// Sets the loading screen widget class to display inside of the loading screen widget host
	UFUNCTION(BlueprintCallable)
	MODULE_API void SetLoadingScreenContentWidget(TSubclassOf<UUserWidget> InNewWidgetClass);

	// Returns the last set loading screen widget class to display inside of the loading screen widget host
	UFUNCTION(BlueprintPure)
	TSubclassOf<class UUserWidget> GetLoadingScreenContentWidget() const;

private:
	UPROPERTY(BlueprintAssignable, meta=(AllowPrivateAccess))
	FScWLoadingScreenWidgetChangedDelegate OnLoadingScreenWidgetChanged;

	UPROPERTY()
	TSubclassOf<UUserWidget> LoadingScreenWidgetClass;
};
