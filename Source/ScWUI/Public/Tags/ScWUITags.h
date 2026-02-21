// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "NativeGameplayTags.h"

#define MODULE_API SCWUI_API

namespace FScWUITags
{
	// Layers
	MODULE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Game);
	MODULE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_GameMenu);
	MODULE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Menu);
	MODULE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Modal);

	// Extension layers
	MODULE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Extension_Center);
	MODULE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Extension_TopLeft);
	MODULE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Extension_TopRight);
	MODULE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Extension_BottomLeft);
	MODULE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Extension_BottomRight);

	// Actions
	MODULE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Action_Escape);

	// Platform traits
	MODULE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Platform_Trait_Input_PrimaryController);
	MODULE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Platform_Trait_Input_HasStrictControllerPairing);
}

#undef MODULE_API
