// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "ScWActionWidget.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UScWActionWidget : public UCommonActionWidget
{
	GENERATED_BODY()

public:
	UScWActionWidget(const FObjectInitializer& InObjectInitializer);

//~ Editor
public:
	
	UFUNCTION(Category = "CommonActionWidget", BlueprintCallable)
	SCWUI_API void SetDesignTimeKey(const FKey& InKey);
//~ Editor
};
