// QTM Connect For Unreal. Copyright 2018-2022 Qualisys
//
#include "QTMConnect.h"

#include <Interfaces/IPluginManager.h>
#include <Misc/MessageDialog.h>
#include <Misc/Paths.h>
#include <HAL/PlatformProcess.h>

#include <Windows/AllowWindowsPlatformTypes.h>
#include <Windows/AllowWindowsPlatformAtomics.h>
#include "RTProtocol.h"
#include <Windows/HideWindowsPlatformAtomics.h>
#include <Windows/HideWindowsPlatformTypes.h>

#define LOCTEXT_NAMESPACE "QTMConnect"

#if PLATFORM_WINDOWS
    #define QTMCONNECT_LOAD_DLL 1
#else
    #error Unsupported build platform
#endif

class FQTMConnectModule : public IQTMConnectPlugin
{
public:
	// IModuleInterface implementation
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// IQTMConnectPlugin implementation
	virtual CRTProtocol* CreateRTObject() override;
	virtual void DestroyRTObject(class CRTProtocol* pClient) override;
};

// This code will execute after your module is loaded into memory; the exact timing depends on the per-module LoadingPhase specified in the .uplugin file.
void FQTMConnectModule::StartupModule()
{
}

// This function may be called during shutdown to clean up your module.
// For modules that support dynamic reloading, we call this function before unloading the module.
void FQTMConnectModule::ShutdownModule()
{
}

CRTProtocol* FQTMConnectModule::CreateRTObject()
{
    return new CRTProtocol();
}

void FQTMConnectModule::DestroyRTObject(CRTProtocol* rtProtocol)
{
    if (rtProtocol)
    {
        delete rtProtocol;
    }
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FQTMConnectModule, QTMConnect)
