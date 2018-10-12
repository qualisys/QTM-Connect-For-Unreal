// QTM Connect For Unreal. Copyright 2018 Qualisys
//
#include "QTMConnect.h"

#include <IPluginManager.h>
#include <MessageDialog.h>
#include <Paths.h>
#include <PlatformProcess.h>

#include "AllowWindowsPlatformTypes.h"
#include "AllowWindowsPlatformAtomics.h"
#include <RTProtocol.h>
#include "HideWindowsPlatformAtomics.h"
#include "HideWindowsPlatformTypes.h"

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

private:
#if QTMCONNECT_LOAD_DLL
	void* mRTClientSDKHandle;
#endif
};

// This code will execute after your module is loaded into memory; the exact timing depends on the per-module LoadingPhase specified in the .uplugin file.
void FQTMConnectModule::StartupModule()
{
#if QTMCONNECT_LOAD_DLL
	// Note: These paths correspond to the RuntimeDependency specified in the .Build.cs script.
	const FString PluginBaseDir = IPluginManager::Get().FindPlugin("QTMConnect")->GetBaseDir();

#if PLATFORM_WINDOWS && PLATFORM_64BITS
	const FString LibraryPath = FPaths::Combine(*PluginBaseDir, TEXT("ThirdParty/RTClientSDK/Lib/Win64/RTClientSDK.dll"));
#elif PLATFORM_WINDOWS && PLATFORM_32BITS
	const FString LibraryPath = FPaths::Combine(*PluginBaseDir, TEXT("ThirdParty/RTClientSDK/Lib/Win32/RTClientSDK.dll"));
#else
#	error Path to QTMConnect shared library not specified for this platform!
#endif

	mRTClientSDKHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;
	if (mRTClientSDKHandle == nullptr)
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("RTClientSDK dll load error", "Error: Failed to load RTClientSDK.dll. Wrong path?"));
	}
#endif

}

// This function may be called during shutdown to clean up your module.
// For modules that support dynamic reloading, we call this function before unloading the module.
void FQTMConnectModule::ShutdownModule()
{
#if QTMCONNECT_LOAD_DLL
	// Unload the DLL.
	if (mRTClientSDKHandle != nullptr)
	{
		FPlatformProcess::FreeDllHandle(mRTClientSDKHandle);
		mRTClientSDKHandle = nullptr;
	}
#endif
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
