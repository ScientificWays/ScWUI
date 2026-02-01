// Scientific Ways

#pragma once

#include "Logging/LogMacros.h"

class UObject;

SCWUI_API DECLARE_LOG_CATEGORY_EXTERN(LogScWUI, Log, All);

SCWUI_API FString GetClientServerContextString(UObject* InContext = nullptr);
