// Scientific Ways

#include "Widgets/ScWActionWidget.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWActionWidget)

UScWActionWidget::UScWActionWidget(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{

}

//~ Editor
void UScWActionWidget::SetDesignTimeKey(const FKey& InKey)
{
	DesignTimeKey = InKey;
	UpdateActionWidget();
}
//~ Editor
