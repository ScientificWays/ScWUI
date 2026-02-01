// Scientific Ways

#include "ScWGameViewportClient.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWGameViewportClient)

class UGameInstance;

namespace GameViewportTags
{
	UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_Platform_Trait_Input_HardwareCursor, "Platform.Trait.Input.HardwareCursor");
}

UScWGameViewportClient::UScWGameViewportClient(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{

}

void UScWGameViewportClient::Init(struct FWorldContext& InWorldContext, UGameInstance* InOwningGameInstance, bool bInCreateNewAudioDevice)
{
	Super::Init(InWorldContext, InOwningGameInstance, bInCreateNewAudioDevice);
	
	// We have software cursors set up in our project settings for console/mobile use, but on desktop we're fine with
	// the standard hardware cursors
	const bool UseHardwareCursor = ICommonUIModule::GetSettings().GetPlatformTraits().HasTag(GameViewportTags::TAG_Platform_Trait_Input_HardwareCursor);
	SetUseSoftwareCursorWidgets(!UseHardwareCursor);
}
