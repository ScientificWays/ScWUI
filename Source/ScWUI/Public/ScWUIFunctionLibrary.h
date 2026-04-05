// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "ScWUIFunctionLibrary.generated.h"

#define MODULE_API SCWUI_API

/**
 *	Static Blueprint function library for common ScW UI operations.
 */
UCLASS(MinimalAPI)
class UScWUIFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};

#undef MODULE_API
