// Scientific Ways

#pragma once

#include "ScWUI.h"

#include "Messaging/ScWMessagingSubsystem.h"

#include "ScWGameDialog.generated.h"

USTRUCT(BlueprintType)
struct FScWConfirmationDialogAction
{
	GENERATED_BODY()

public:
	/** Required: The dialog option to provide. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EScWMessagingResult Result = EScWMessagingResult::Unknown;

	/** Optional: Display Text to use instead of the action name associated with the result. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText OptionalDisplayText;

	bool operator==(const FScWConfirmationDialogAction& InOther) const
	{
		return Result == InOther.Result &&
			OptionalDisplayText.EqualTo(InOther.OptionalDisplayText);
	}
};

UCLASS(MinimalAPI)
class UScWGameDialogDescriptor : public UObject
{
	GENERATED_BODY()
	
public:
	static MODULE_API UScWGameDialogDescriptor* CreateConfirmationOk(const FText& Header, const FText& Body);
	static MODULE_API UScWGameDialogDescriptor* CreateConfirmationOkCancel(const FText& Header, const FText& Body);
	static MODULE_API UScWGameDialogDescriptor* CreateConfirmationYesNo(const FText& Header, const FText& Body);
	static MODULE_API UScWGameDialogDescriptor* CreateConfirmationYesNoCancel(const FText& Header, const FText& Body);

public:
	/** The header of the message to display */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Header;
	
	/** The body of the message to display */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Body;

	/** The confirm button's input action to use. */
	UPROPERTY(BlueprintReadWrite)
	TArray<FScWConfirmationDialogAction> ButtonActions;
};


UCLASS(MinimalAPI, Abstract)
class UScWGameDialog : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	MODULE_API UScWGameDialog();
	
	MODULE_API virtual void SetupDialog(UScWGameDialogDescriptor* Descriptor, FCommonMessagingResultDelegate ResultCallback);

	MODULE_API virtual void KillDialog();
};
