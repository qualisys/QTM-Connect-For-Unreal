// QTM Connect For Unreal. Copyright 2018-2022 Qualisys
//
#include "QTMConnectLiveLinkBlueprint.h"
#include "ILiveLinkClient.h"
#include "Features/IModularFeature.h"
#include "Features/IModularFeatures.h"
#include "QTMConnectLiveLinkSource.h"

void UQTMConnectLiveLinkBlueprint::CreateQTMConnectLiveLinkSource(FString IpAddress, bool Stream3d, bool Stream6d, bool StreamSkeleton, bool StreamForce, FString StreamRate, int FrequencyValue, FLiveLinkSourceHandle& SourceHandle)
{
    IModularFeatures& ModularFeatures = IModularFeatures::Get();

    TSharedPtr<FQTMConnectLiveLinkSource> livelinkSource = nullptr;
    if (ModularFeatures.IsModularFeatureAvailable(ILiveLinkClient::ModularFeatureName))
    {
        ILiveLinkClient* LiveLinkClient = &ModularFeatures.GetModularFeature<ILiveLinkClient>(ILiveLinkClient::ModularFeatureName);

        QTMConnectLiveLinkSettings settings;
        settings.IpAddress = IpAddress;
        settings.Stream3d = Stream3d;
        settings.Stream6d = Stream6d;
        settings.StreamSkeleton = StreamSkeleton;
        settings.StreamForce = StreamForce;
        settings.StreamRate = StreamRate;
        settings.FrequencyValue = FrequencyValue;

        livelinkSource = MakeShareable(new FQTMConnectLiveLinkSource(settings));
        LiveLinkClient->AddSource(livelinkSource);
    }
    SourceHandle.SetSourcePointer(livelinkSource);
}
