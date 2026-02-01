// Scientific Ways

#include "ScWLoadingScreenSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWLoadingScreenSubsystem)

UScWLoadingScreenSubsystem::UScWLoadingScreenSubsystem()
{

}

void UScWLoadingScreenSubsystem::SetLoadingScreenContentWidget(TSubclassOf<UUserWidget> InNewWidgetClass)
{
	if (LoadingScreenWidgetClass != InNewWidgetClass)
	{
		LoadingScreenWidgetClass = InNewWidgetClass;

		OnLoadingScreenWidgetChanged.Broadcast(LoadingScreenWidgetClass);
	}
}

TSubclassOf<UUserWidget> UScWLoadingScreenSubsystem::GetLoadingScreenContentWidget() const
{
	return LoadingScreenWidgetClass;
}

