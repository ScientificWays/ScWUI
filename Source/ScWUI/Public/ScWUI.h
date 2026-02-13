// Scientific Ways

#pragma once

#include "CoreMinimal.h"

#include "UObject/Stack.h"
#include "UObject/UObjectHash.h"
#include "UObject/SoftObjectPtr.h"

#include "GenericPlatform/GenericPlatformApplicationMisc.h"
#include "GenericPlatform/GenericPlatformInputDeviceMapper.h"

#include "Engine/World.h"
#include "Engine/DataTable.h"
#include "Engine/LocalPlayer.h"
#include "Engine/AssetManager.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"

#include "Framework/Application/SlateApplication.h"

#include "NativeGameplayTags.h"
#include "GameplayTagContainer.h"

#include "Blueprint/UserWidget.h"
#include "EnhancedInputSubsystemInterface.h"

#include "GameFramework/InputSettings.h"
#include "GameFramework/InputDeviceSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Components/HorizontalBox.h"
#include "Components/DynamicEntryBox.h"
#include "Components/GameFrameworkComponentManager.h"

#include "ICommonUIModule.h"
#include "ICommonInputModule.h"

#include "CommonBorder.h"
#include "CommonTextBlock.h"
#include "CommonUISettings.h"
#include "CommonButtonBase.h"
#include "CommonActionWidget.h"
#include "CommonRichTextBlock.h"
#include "CommonInputTypeEnum.h"
#include "CommonInputSubsystem.h"
#include "CommonActivatableWidget.h"
#include "CommonGameViewportClient.h"
#include "Input/CommonUIInputTypes.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include "Containers/Ticker.h"

#include "Modules/ModuleInterface.h"

#if WITH_EDITOR
	#include "CommonInputSettings.h"
	#include "Editor/WidgetCompilerLog.h"
	#include "CommonUIVisibilitySubsystem.h"
#endif	// WITH_EDITOR

#include "Utils/ScWUtils.h"

DECLARE_LOG_CATEGORY_EXTERN(LogScWUI, Log, All);

class FScWUIModule : public IModuleInterface
{
public:
	virtual void StartupModule() override; // IModuleInterface
	virtual void ShutdownModule() override; // IModuleInterface
};
