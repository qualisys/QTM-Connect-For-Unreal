// QTM Connect For Unreal. Copyright 2018-2026 Qualisys
//
#pragma once

#include "CoreMinimal.h"
#include "LiveLinkDevice.h"
#include "LiveLinkDeviceCapability_Connection.h"
#include "LiveLinkDeviceCapability_Recording.h"
#include "Templates/UniquePtr.h"

// Full include (not forward decl): TUniquePtr<FQTMRecordingController> requires
// the destructor to be visible when the UCLASS's auto-generated dtor is emitted
// in QTMLiveLinkDevice.gen.cpp.
#include "QTMRecordingController.h"

#include "QTMLiveLinkDevice.generated.h"


/** User-editable settings for the QTM Live Link device. */
UCLASS()
class UQTMLiveLinkDeviceSettings : public ULiveLinkDeviceSettings
{
    GENERATED_BODY()

public:
    // NOTE: ULiveLinkDeviceSettings (UE 5.8+) provides its own DisplayName UPROPERTY,
    // which the device manager UI surfaces directly. Don't redeclare it here.

    /** Hostname or IP of the QTM machine. */
    UPROPERTY(EditAnywhere, Category = "QTM|Connection")
    FString Host = TEXT("127.0.0.1");

    /** QTM RT-protocol port (22222 by default). */
    UPROPERTY(EditAnywhere, Category = "QTM|Connection", meta = (ClampMin = "1", ClampMax = "65535"))
    int32 Port = 22222;

    /** TakeControl password. Leave empty if no password is configured in QTM. */
    UPROPERTY(EditAnywhere, Category = "QTM|Connection")
    FString Password;

    /**
     * Optional override for the directory where captures are saved (on the QTM machine).
     * Empty = trust QTM's current project directory.
     */
    UPROPERTY(EditAnywhere, Category = "QTM|Recording")
    FString CaptureDirectoryOverride;

    /**
     * Filename template for SaveCapture, resolved from the active Take Recorder slate/take.
     * Supported tokens:
     *   {Slate}, {Session}, {Take}, {Take:Nd} (zero-padded to N digits)
     */
    UPROPERTY(EditAnywhere, Category = "QTM|Recording")
    FString FilenameTemplate = TEXT("{Slate}_{Take:03d}");
};


UCLASS()
class UQTMLiveLinkDevice
    : public ULiveLinkDevice
    , public ILiveLinkDeviceCapability_Connection
    , public ILiveLinkDeviceCapability_Recording
{
    GENERATED_BODY()

public:
    //~ Begin ULiveLinkDevice interface
    virtual TSubclassOf<ULiveLinkDeviceSettings> GetSettingsClass() const override
    {
        return UQTMLiveLinkDeviceSettings::StaticClass();
    }
    // GetDisplayName not overridden: the base class implementation in UE 5.8 reads
    // the inherited Settings->DisplayName UPROPERTY, which is exactly what we want.
    virtual EDeviceHealth GetDeviceHealth() const override;
    virtual FText GetHealthText() const override;

    virtual void OnDeviceAdded() override;
    virtual void OnDeviceRemoved() override;
    //~ End ULiveLinkDevice interface

    //~ Begin ILiveLinkDeviceCapability_Connection interface
    virtual ELiveLinkDeviceConnectionStatus GetConnectionStatus_Implementation() const override;
    virtual FString GetHardwareId_Implementation() const override;
    virtual bool CanSetHardwareId_Implementation() override { return true; }
    virtual bool SetHardwareId_Implementation(const FString& HardwareID) override;
    virtual bool Connect_Implementation() override;
    virtual bool Disconnect_Implementation() override;
    //~ End ILiveLinkDeviceCapability_Connection interface

    //~ Begin ILiveLinkDeviceCapability_Recording interface
    virtual bool StartRecording_Implementation() override;
    virtual bool StopRecording_Implementation() override;
    virtual bool IsRecording_Implementation() const override;
    //~ End ILiveLinkDeviceCapability_Recording interface

private:
    /** Build the destination filename by resolving the user template against the current session. */
    FString BuildDestinationPath() const;

    TUniquePtr<FQTMRecordingController> Controller;
};
