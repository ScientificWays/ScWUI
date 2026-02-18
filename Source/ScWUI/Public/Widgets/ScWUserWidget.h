// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "ScWUserWidget.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI, Abstract, Blueprintable, meta = (DisplayName = "[ScW] User Widget"))
class UScWUserWidget : public UCommonUserWidget
{
	GENERATED_BODY()
	
//~ Begin Initialize
public:
	UScWUserWidget(const FObjectInitializer& InObjectInitializer);
	
	UFUNCTION(Category = "Initialize", BlueprintCallable, BlueprintNativeEvent, meta = (DisplayName = "Remove Animated"))
	void BP_RemoveAnimated();
//~ End Initialize
};
