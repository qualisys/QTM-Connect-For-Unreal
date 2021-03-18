#ifndef RTPACKET_H
#define RTPACKET_H

#include <vector>

#ifdef _WIN32
#pragma warning (disable : 4251)
#endif

#ifdef EXPORT_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT
#endif

#define MAJOR_VERSION           1
#define MINOR_VERSION           21

class DLL_EXPORT CRTPacket
{
public:
    enum EPacketType
    {
        PacketError       = 0,
        PacketCommand     = 1,
        PacketXML         = 2,
        PacketData        = 3,
        PacketNoMoreData  = 4,
        PacketC3DFile     = 5,
        PacketEvent       = 6,
        PacketDiscover    = 7,
        PacketQTMFile     = 8,
        PacketNone        = 9
    };

    enum EComponentType 
    {
        Component3d            = 1,
        Component3dNoLabels    = 2,
        ComponentAnalog        = 3,
        ComponentForce         = 4,
        Component6d            = 5,
        Component6dEuler       = 6,
        Component2d            = 7,
        Component2dLin         = 8,
        Component3dRes         = 9,
        Component3dNoLabelsRes = 10,
        Component6dRes         = 11,
        Component6dEulerRes    = 12,
        ComponentAnalogSingle  = 13,
        ComponentImage         = 14,
        ComponentForceSingle   = 15,
        ComponentGazeVector    = 16,
        ComponentTimecode      = 17,
        ComponentSkeleton      = 18,
        ComponentEyeTracker    = 19,
        ComponentNone          = 20
    };

    enum EImageFormat
    {
        FormatRawGrayscale = 0,
        FormatRawBGR       = 1,
        FormatJPG          = 2,
        FormatPNG          = 3
    };

    enum EEvent
    {
        EventConnected               = 1,
        EventConnectionClosed        = 2,
        EventCaptureStarted          = 3,
        EventCaptureStopped          = 4,
        EventCaptureFetchingFinished = 5, // Not used in version 1.10 and later
        EventCalibrationStarted      = 6,
        EventCalibrationStopped      = 7,
        EventRTfromFileStarted       = 8,
        EventRTfromFileStopped       = 9,
        EventWaitingForTrigger       = 10,
        EventCameraSettingsChanged   = 11,
        EventQTMShuttingDown         = 12,
        EventCaptureSaved            = 13,
        EventReprocessingStarted     = 14,
        EventReprocessingStopped     = 15,
        EventTrigger                 = 16,
        EventNone                    = 17  // Must be the last. Not actually an event. Just used to cont number of events.
    };

    enum ETimecodeType
    {
        TimecodeSMPTE = 0,
        TimecodeIRIG = 1,
        TimecodeCamerTime = 2
    };

    struct SForce
    {
        float fForceX;
        float fForceY;
        float fForceZ;
        float fMomentX;
        float fMomentY;
        float fMomentZ;
        float fApplicationPointX;
        float fApplicationPointY;
        float fApplicationPointZ;
    };

    struct SGazeVector
    {
        float fX;
        float fY;
        float fZ;
        float fPosX;
        float fPosY;
        float fPosZ;
    };

    struct SEyeTracker
    {
        float leftPupilDiameter;
        float rightPupilDiameter;
    };

    struct SPosition
    {
        float x;
        float y;
        float z;
    };

    struct SRotation
    {
        float x;
        float y;
        float z;
        float w;
    };

    struct SSkeletonSegment
    {
        unsigned int id;
        float positionX;
        float positionY;
        float positionZ;
        float rotationX;
        float rotationY;
        float rotationZ;
        float rotationW;
    };

public:
    CRTPacket(int nMajorVersion = MAJOR_VERSION, int nMinorVersion = MINOR_VERSION, bool bBigEndian = false);
    void             GetVersion(unsigned int &nMajorVersion, unsigned int &nMinorVersion);
    void             SetVersion(unsigned int nMajorVersion, unsigned int nMinorVersion);
    bool             GetEndianness();
    void             SetEndianness(bool bBigEndian);
    void             ClearData();
    void             SetData(char* ptr);
    void             GetData(char* &ptr, unsigned int &nSize);

    unsigned int     GetSize();
    EPacketType      GetType();
    unsigned long long GetTimeStamp();
    unsigned int     GetFrameNumber();
    static unsigned int     GetSize(char* pData, bool bBigEndian = false);
    static EPacketType      GetType(char* pData, bool bBigEndian = false);
    static unsigned long long GetTimeStamp(char* pData, bool bBigEndian = false);
    static unsigned int     GetFrameNumber(char* pData, bool bBigEndian = false);

    unsigned int     GetComponentCount();
    unsigned int     GetComponentSize(EComponentType eComponent);

    char*            GetErrorString();
    char*            GetCommandString();
    static char*     GetCommandString(char* pData, bool bBigEndian = false);
    char*            GetXMLString();
    bool             GetEvent(EEvent &eEvent);
    static bool      GetEvent(EEvent &eEvent, char* pData, bool bBigEndian = false);
    short            GetDiscoverResponseBasePort();
    static short     GetDiscoverResponseBasePort(char* pData, bool bBigEndian = false);

    unsigned short   GetDropRate();
    unsigned short   GetOutOfSyncRate();

    unsigned int     Get2DCameraCount();
    unsigned int     Get2DMarkerCount(unsigned int nCameraIndex);
    unsigned char    Get2DStatusFlags(unsigned int nCameraIndex);
    bool             Get2DMarker(unsigned int nCameraIndex, unsigned int nMarkerIndex, unsigned int &nX,
                                     unsigned int &nY, unsigned short &nXDiameter, unsigned short & nYDiameter);

    unsigned int     Get2DLinCameraCount();
    unsigned int     Get2DLinMarkerCount(unsigned int nCameraIndex);
    unsigned char    Get2DLinStatusFlags(unsigned int nCameraIndex);
    bool             Get2DLinMarker(unsigned int nCameraIndex, unsigned int nMarkerIndex, unsigned int &nX,
                                        unsigned int &nY, unsigned short &nXDiameter, unsigned short & nYDiameter);

    unsigned int     Get3DMarkerCount();
    bool             Get3DMarker(unsigned int nMarkerIndex, float &fX, float &fY, float &fZ);

    unsigned int     Get3DResidualMarkerCount();
    bool             Get3DResidualMarker(unsigned int nMarkerIndex, float &fX, float &fY, float &fZ,
                                             float &fResidual);

    unsigned int     Get3DNoLabelsMarkerCount();
    bool             Get3DNoLabelsMarker(unsigned int nMarkerIndex, float &fX, float &fY, float &fZ,
                                         unsigned int &nId);

    unsigned int     Get3DNoLabelsResidualMarkerCount();
    bool             Get3DNoLabelsResidualMarker(unsigned int nMarkerIndex, float &fX, float &fY, float &fZ,
                                                 unsigned int &nId, float &fResidual);


    unsigned int     Get6DOFBodyCount();
    bool             Get6DOFBody(unsigned int nBodyIndex, float &fX, float &fY, float &fZ, float afRotMatrix[9]);

    unsigned int     Get6DOFResidualBodyCount();
    bool             Get6DOFResidualBody(unsigned int nBodyIndex, float &fX, float &fY, float &fZ,
                                         float afRotMatrix[9], float &fResidual);

    unsigned int     Get6DOFEulerBodyCount();
    bool             Get6DOFEulerBody(unsigned int nBodyIndex, float &fX, float &fY, float &fZ,
                                      float &fAng1, float &fAng2, float &fAng3);

    unsigned int     Get6DOFEulerResidualBodyCount();
    bool             Get6DOFEulerResidualBody(unsigned int nBodyIndex, float &fX, float &fY, float &fZ,
                                                  float &fAng1, float &fAng2, float &fAng3, float &fResidual);

    unsigned int     GetGazeVectorCount();
    unsigned int     GetGazeVectorSampleCount(unsigned int nVectorIndex);
    unsigned int     GetGazeVectorSampleNumber(unsigned int nVectorIndex); // Returns 0 if no sample was found.
    bool             GetGazeVector(unsigned int nVectorIndex, unsigned int nSampleIndex, SGazeVector &nGazeVector);
    bool             GetGazeVector(unsigned int nVectorIndex, SGazeVector* pGazeVectorBuf, unsigned int nBufSize);

    unsigned int     GetEyeTrackerCount();
    unsigned int     GetEyeTrackerSampleCount(unsigned int eyeTrackerIndex);
    unsigned int     GetEyeTrackerSampleNumber(unsigned int eyeTrackerIndex); // Returns 0 if no sample was found.
    bool             GetEyeTrackerData(unsigned int eyeTrackerIndex, unsigned int nSampleIndex, SEyeTracker &nEyeTracker);
    bool             GetEyeTrackerData(unsigned int eyeTrackerIndex, SEyeTracker* pEyeTrackerBuf, unsigned int nBufSize);

    bool             IsTimeCodeAvailable() const;
    bool             GetTimecodeType(CRTPacket::ETimecodeType &timecodeType);
    bool             GetTimecodeSMPTE(int &hours, int &minutes, int &seconds, int &frames);
    bool             GetTimecodeIRIG(int &years, int &days, int &hours, int &minutes, int &seconds, int &tenths);
    bool             GetTimecodeCameraTime(unsigned long long &cameraTime);

    unsigned int     GetImageCameraCount();
    unsigned int     GetImageCameraId(unsigned int nCameraIndex);
    bool             GetImageFormat(unsigned int nCameraIndex, EImageFormat &eImageFormat);
    bool             GetImageSize(unsigned int nCameraIndex, unsigned int &nWidth, unsigned int &nHeight);                              
    bool             GetImageCrop(unsigned int nCameraIndex, float &fCropLeft, float &fCropTop,
                                  float &fCropRight, float &fCropBottom);
    unsigned int     GetImageSize(unsigned int nCameraIndex);
    unsigned int     GetImage(unsigned int nCameraIndex, char* pDataBuf, unsigned int nBufSize);

    unsigned int     GetAnalogDeviceCount();
    unsigned int     GetAnalogDeviceId(unsigned int nDeviceIndex);
    unsigned int     GetAnalogChannelCount(unsigned int nDeviceIndex);
    unsigned int     GetAnalogSampleCount(unsigned int nDeviceIndex);
    unsigned int     GetAnalogSampleNumber(unsigned int nDeviceIndex); // Returns 0 if no sample was found.
    unsigned int     GetAnalogData(unsigned int nDeviceIndex, float* pDataBuf, unsigned int nBufSize);
    unsigned int     GetAnalogData(unsigned int nDeviceIndex, unsigned int nChannelIndex, float* pDataBuf, unsigned int nBufSize);
    bool             GetAnalogData(unsigned int nDeviceIndex, unsigned int nChannelIndex,
                                   unsigned int nSampleIndex, float &fAnalogValue);

    unsigned int     GetAnalogSingleDeviceCount();
    unsigned int     GetAnalogSingleDeviceId(unsigned int nDeviceIndex);
    unsigned int     GetAnalogSingleChannelCount(unsigned int nDeviceIndex);
    unsigned int     GetAnalogSingleData(unsigned int nDeviceIndex, float* pDataBuf, unsigned int nBufSize);
    bool             GetAnalogSingleData(unsigned int nDeviceIndex, unsigned int nChannelIndex, float &fValue);

    unsigned int     GetForcePlateCount();
    unsigned int     GetForcePlateId(unsigned int nPlateIndex);
    unsigned int     GetForceCount(unsigned int nPlateIndex);
    unsigned int     GetForceNumber(unsigned int nPlateIndex);// Returns 0 if no force was found.
    unsigned int     GetForceData(unsigned int nPlateIndex, SForce* pForceBuf, unsigned int nBufSize);
    bool             GetForceData(unsigned int nPlateIndex, unsigned int nForceIndex, SForce &sForce);

    unsigned int     GetForceSinglePlateCount();
    unsigned int     GetForceSinglePlateId(unsigned int nPlateIndex);
    bool             GetForceSingleData(unsigned int nPlateIndex, SForce &pForce);

    unsigned int     GetSkeletonCount();
    unsigned int     GetSkeletonSegmentCount(unsigned int nSkeletonIndex);
    bool             GetSkeletonSegments(unsigned int nSkeletonIndex, SSkeletonSegment* segmentBuf, unsigned int nBufSize);
    bool             GetSkeletonSegment(unsigned int nSkeletonIndex, unsigned segmentIndex, SSkeletonSegment &segment);

private:
    float            SetByteOrder(float* pfData);
    double           SetByteOrder(double* pfData);
    short            SetByteOrder(short* pnData);
    unsigned short   SetByteOrder(unsigned short* pnData);
    long             SetByteOrder(long* pnData);
    int              SetByteOrder(int* pnData);
    unsigned int     SetByteOrder(unsigned int* pnData);
    long long        SetByteOrder(long long* pnData);
    unsigned long long SetByteOrder(unsigned long long* pnData);

private:
    char*          mpData;
    std::vector<char*> mpComponentData;
    std::vector<char*> mp2DData;
    std::vector<char*> mp2DLinData;
    std::vector<char*> mpImageData;
    std::vector<char*> mpAnalogData;
    std::vector<char*> mpAnalogSingleData;
    std::vector<char*> mpForceData;
    std::vector<char*> mpForceSingleData;
    std::vector<char*> mpGazeVectorData;
    std::vector<char*> mpEyeTrackerData;
    std::vector<char*> mpTimecodeData;
    std::vector<char*> mpSkeletonData;
    unsigned int   mnComponentCount;
    EComponentType meComponentType;
    unsigned int   mn2DCameraCount;
    unsigned int   mn2DLinCameraCount;
    unsigned int   mnImageCameraCount;
    unsigned int   mnAnalogDeviceCount;
    unsigned int   mnAnalogSingleDeviceCount;
    unsigned int   mnForcePlateCount;
    unsigned int   mnForceSinglePlateCount;
    unsigned int   mnGazeVectorCount;
    unsigned int   mnEyeTrackerCount;
    unsigned int   mnTimecodeCount;
    unsigned int   mSkeletonCount;
    int            mnMajorVersion;
    int            mnMinorVersion;
    bool           mbBigEndian;
}; // RTPacket


#endif // RTPACKET_H