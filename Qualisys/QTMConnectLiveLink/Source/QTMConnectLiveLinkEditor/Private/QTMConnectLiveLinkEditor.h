// QTM Connect For Unreal. Copyright 2018-2022 Qualisys
//
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FQTMConnectLiveLinkEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};