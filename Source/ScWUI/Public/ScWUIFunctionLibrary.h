// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "ScWUIFunctionLibrary.generated.h"

UCLASS(MinimalAPI)
class UScWUIFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UScWUIFunctionLibrary() { }
	
	UFUNCTION(Category = "ScW | UI", BlueprintPure, BlueprintCosmetic, meta = (WorldContext = "InContextWidget"))
	static MODULE_API ECommonInputType GetOwningPlayerInputType(const UUserWidget* InContextWidget);
	
	UFUNCTION(Category = "ScW | UI", BlueprintPure, BlueprintCosmetic, meta = (WorldContext = "InContextWidget"))
	static MODULE_API bool IsOwningPlayerUsingTouch(const UUserWidget* InContextWidget);

	UFUNCTION(Category = "ScW | UI", BlueprintPure, BlueprintCosmetic, meta = (WorldContext = "InContextWidget"))
	static MODULE_API bool IsOwningPlayerUsingGamepad(const UUserWidget* InContextWidget);

	UFUNCTION(Category = "ScW | UI", BlueprintCallable, BlueprintCosmetic)
	static MODULE_API UCommonActivatableWidget* PushContentToLayer_ForPlayer(const ULocalPlayer* InLocalPlayer, UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerName, UPARAM(meta = (AllowAbstract = false)) TSubclassOf<UCommonActivatableWidget> WidgetClass);

	UFUNCTION(Category = "ScW | UI", BlueprintCallable, BlueprintCosmetic)
	static MODULE_API void PushStreamedContentToLayer_ForPlayer(const ULocalPlayer* InLocalPlayer, UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerName, UPARAM(meta = (AllowAbstract = false)) TSoftClassPtr<UCommonActivatableWidget> WidgetClass);

	UFUNCTION(Category = "ScW | UI", BlueprintCallable, BlueprintCosmetic)
	static MODULE_API void PopContentFromLayer(UCommonActivatableWidget* ActivatableWidget);

	UFUNCTION(Category = "ScW | UI", BlueprintCallable, BlueprintCosmetic)
	static MODULE_API ULocalPlayer* GetLocalPlayerFromController(APlayerController* InPlayerController);

	UFUNCTION(Category = "ScW | UI", BlueprintCallable, BlueprintCosmetic)
	static MODULE_API FName SuspendInputForPlayer(APlayerController* InPlayerController, FName InSuspendReason);
	static MODULE_API FName SuspendInputForPlayer(ULocalPlayer* InLocalPlayer, FName InSuspendReason);

	UFUNCTION(Category = "ScW | UI", BlueprintCallable, BlueprintCosmetic)
	static MODULE_API void ResumeInputForPlayer(APlayerController* InPlayerController, FName InSuspendToken);
	static MODULE_API void ResumeInputForPlayer(ULocalPlayer* InLocalPlayer, FName InSuspendToken);
private:
	static MODULE_API int32 InputSuspensions;
};
