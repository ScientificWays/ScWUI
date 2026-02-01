// Scientific Ways

#pragma once

#include "CoreMinimal.h"

class FScWUIModule : public IModuleInterface
{
public:
	virtual void StartupModule() override; // IModuleInterface
	virtual void ShutdownModule() override; // IModuleInterface
};
