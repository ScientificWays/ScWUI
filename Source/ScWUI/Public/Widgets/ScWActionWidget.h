// Scientific Ways

#pragma once

#include "CoreMinimal.h"
#include "CommonActionWidget.h"
#include "ScWActionWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCWUI_API UScWActionWidget : public UCommonActionWidget
{
	GENERATED_BODY()

public:
	UScWActionWidget(const FObjectInitializer& InObjectInitializer);

//~ Editor
public:
	
	UFUNCTION(Category = "CommonActionWidget", BlueprintCallable)
	void SetDesignTimeKey(const FKey& InKey);
//~ Editor
};
