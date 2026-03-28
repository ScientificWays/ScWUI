// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "ScWActionWidget.generated.h"

#define MODULE_API SCWUI_API

/**
 *	Action widget with editor-time key preview support.
 */
UCLASS(MinimalAPI, meta = (DisplayName = "[ScW] Action Widget"))
class UScWActionWidget : public UCommonActionWidget
{
	GENERATED_BODY()

public:
	UScWActionWidget(const FObjectInitializer& InObjectInitializer);

//~ Begin Editor
public:
	UFUNCTION(Category = "CommonActionWidget", BlueprintCallable)
	MODULE_API void SetDesignTimeKey(const FKey& InKey);
//~ End Editor
};

#undef MODULE_API
