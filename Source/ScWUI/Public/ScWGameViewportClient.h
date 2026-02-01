// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "ScWGameViewportClient.generated.h"

UCLASS(MinimalAPI, BlueprintType, meta = (DisplayName = "[ScW] Game Viewport Client"))
class UScWGameViewportClient : public UCommonGameViewportClient
{
	GENERATED_BODY()

public:
	UScWGameViewportClient(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());
protected:
	virtual void Init(struct FWorldContext& InWorldContext, class UGameInstance* InOwningGameInstance, bool bInCreateNewAudioDevice = true) override; // UGameViewportClient
};
