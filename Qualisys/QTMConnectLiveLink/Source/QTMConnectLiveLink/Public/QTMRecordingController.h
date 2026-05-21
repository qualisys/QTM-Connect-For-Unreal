// QTM Connect For Unreal. Copyright 2018-2026 Qualisys
//
#pragma once

#include "CoreMinimal.h"
#include "Containers/Queue.h"
#include "HAL/CriticalSection.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "HAL/ThreadSafeBool.h"
#include "Templates/Atomic.h"

#include <memory>

class CRTProtocol;


/**
 * Connection state mirrored from the worker's CRTProtocol session.
 * Mapped to ELiveLinkDeviceConnectionStatus at the device layer.
 */
enum class EQTMControllerStatus : uint8
{
    Disconnected,
    Connecting,
    Connected,
    Disconnecting,
};


/**
 * Worker that owns a dedicated CRTProtocol instance for *recording control*.
 *
 * Lives in the QTMConnectLiveLink runtime module (where the RT SDK is vendored)
 * and is exported via QTMCONNECTLIVELINK_API so the editor-only
 * QTMConnectLiveLinkDevice module can construct/drive it without pulling in the
 * SDK headers itself.
 *
 * Intentionally separate from FQTMConnectLiveLinkSource: that source owns its own
 * RT connection for the data stream (port 22222), and this controller opens a
 * *second* connection to the same QTM for issuing TakeControl / StartCapture /
 * StopCapture / SaveCapture commands. The two paths are decoupled so a user can
 * use either independently.
 *
 * State machine (driven on the worker thread):
 *
 *   Idle  --Connect-->  Connecting  --(success)-->  Connected
 *                                  \-(fail)-------->  Idle (with error)
 *   Connected  --StartRecording-->  Recording
 *   Recording  --StopRecording---->  Stopping  --EventCaptureStopped-->  Saving
 *   Saving     --(SaveCapture ok)->  Connected
 *   Saving     --(retries exhaust)->  Connected  (with error in status text)
 *   Any        --Disconnect------->  Idle
 */
class QTMCONNECTLIVELINK_API FQTMRecordingController : public FRunnable
{
public:
    FQTMRecordingController();
    virtual ~FQTMRecordingController();

    /** Game-thread API. All methods are non-blocking; commands run on the worker. */
    void RequestConnect(const FString& Host, uint16 Port, const FString& Password);
    void RequestDisconnect();
    void RequestStartRecording();
    /** SaveTargetPath may be empty (let QTM use its project directory + default name). */
    void RequestStopRecording(const FString& SaveTargetPath);

    /** Thread-safe status accessors. */
    EQTMControllerStatus GetStatus() const { return Status.Load(); }
    bool IsRecording() const { return bIsRecording; }
    FText GetStatusText() const;
    FString GetLastSavedPath() const;

    /** FRunnable interface. */
    virtual bool Init() override { return true; }
    virtual uint32 Run() override;
    virtual void Stop() override;
    virtual void Exit() override {}

private:
    enum class ECommand : uint8 { Connect, Disconnect, StartRecording, StopRecording, Shutdown };

    struct FCommand
    {
        ECommand Op;
        FString StringArg1; // host or save path
        FString StringArg2; // password
        uint16 IntArg = 0;  // port
    };

    // Worker-side state-machine handlers.
    void Worker_Connect(const FCommand& Cmd);
    void Worker_Disconnect();
    void Worker_StartRecording();
    void Worker_StopRecording(const FString& SaveTargetPath);
    void Worker_PumpEvents();
    void Worker_AttemptSave();

    void SetStatusText(const FText& InText);
    void SetStatus(EQTMControllerStatus InStatus);

    // Thread plumbing.
    FRunnableThread* Thread = nullptr;
    FThreadSafeBool bStopRequested;
    TQueue<FCommand, EQueueMode::Mpsc> CommandQueue;

    // Owned only by the worker thread once started.
    std::shared_ptr<CRTProtocol> RTProtocol;

    // Save-after-stop bookkeeping (worker-thread only).
    bool bSavePending = false;
    FString PendingSavePath;
    int32 SaveAttempt = 0;
    double NextSaveAttemptSeconds = 0.0;

    // Cross-thread state.
    TAtomic<EQTMControllerStatus> Status { EQTMControllerStatus::Disconnected };
    FThreadSafeBool bIsRecording;

    mutable FCriticalSection StatusLock;
    FText StatusText;
    FString LastSavedPath;
};
