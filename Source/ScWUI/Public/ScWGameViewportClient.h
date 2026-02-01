// Scientific Ways

#pragma once

#include "CommonGameViewportClient.h"

#include "ScWGameViewportClient.generated.h"

UCLASS(BlueprintType, meta = (DisplayName = "[ScW] Game Viewport Client"))
class SCWUI_API UScWGameViewportClient : public UCommonGameViewportClient
{
	GENERATED_BODY()

public:
	UScWGameViewportClient(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());
protected:
	virtual void Init(struct FWorldContext& InWorldContext, class UGameInstance* InOwningGameInstance, bool bInCreateNewAudioDevice = true) override; // UGameViewportClient
};
