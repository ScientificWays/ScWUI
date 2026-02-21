// Scientific Ways

#include "Tags/ScWUITags.h"

//#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWUITags)

namespace FScWUITags
{
	// Layers
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Layer_Game, "UI.Layer.Game", "[Native] Gameplay layer like HUD.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Layer_GameMenu, "UI.Layer.GameMenu", "[Native] Gamelay menus layer like Inventory.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Layer_Menu, "UI.Layer.Menu", "[Native] Non-gameplay menu layer like Pause.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Layer_Modal, "UI.Layer.Modal", "[Native] Non-gameplay pop-up windows layer like Confirm/Cancel.");

	// Extension layers
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Extension_Center, "UI.Extension.Center", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Extension_TopLeft, "UI.Extension.TopLeft", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Extension_TopRight, "UI.Extension.TopRight", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Extension_BottomLeft, "UI.Extension.BottomLeft", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Extension_BottomRight, "UI.Extension.BotoomRight", "[Native] TODO: Add description");

	// Actions
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Action_Escape, "UI.Action.Escape", "[Native] TODO: Add description");

	// Platform traits
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Platform_Trait_Input_PrimaryController, "Platform.Trait.Input.PrimaryController", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Platform_Trait_Input_HasStrictControllerPairing, "Platform.Trait.Input.HasStrictControllerPairing", "[Native] TODO: Add description");
}
