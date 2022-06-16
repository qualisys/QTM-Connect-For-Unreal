// QTM Connect For Unreal. Copyright 2018-2022 Qualisys
//
#pragma once

#include <Modules/ModuleManager.h>

class CRTProtocol;

// QTMConnect plugin module handling
class IQTMConnectPlugin : public IModuleInterface
{
public:
    virtual class CRTProtocol* CreateRTObject() = 0;
    virtual void DestroyRTObject(class CRTProtocol* pClient) = 0;

public:
    // Get a singleton instance of the streaming plugin
    static inline IQTMConnectPlugin& Get()
    {
        return FModuleManager::LoadModuleChecked<IQTMConnectPlugin>("QTMConnect");
    }

    // Check if the singleton streaming instance already has been created
    static inline bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded("QTMConnect");
    }
};
