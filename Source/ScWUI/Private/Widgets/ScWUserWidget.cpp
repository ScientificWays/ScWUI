// Scientific Ways

#include "Widgets/ScWUserWidget.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWUserWidget)

//~ Begin Initialize
UScWUserWidget::UScWUserWidget(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
	
}

void UScWUserWidget::BP_RemoveAnimated_Implementation()
{
	UE_LOG(LogScWUI, Error, TEXT("%hs is not implemented on %s!"), __func__, *GetName());
}
//~ End Initialize
