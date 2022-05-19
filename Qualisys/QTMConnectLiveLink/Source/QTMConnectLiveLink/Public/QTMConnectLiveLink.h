// QTM Connect For Unreal. Copyright 2018-2022 Qualisys
//
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FQTMConnectLiveLinkModule : public IModuleInterface
{
public:

    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
