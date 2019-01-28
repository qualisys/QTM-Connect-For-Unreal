// QTM Connect For Unreal. Copyright 2018-2019 Qualisys
//
#pragma once

#include "LiveLinkSourceFactory.h"
#include "QTMConnectLiveLinkSourceFactory.generated.h"

class SQTMConnectLiveLinkSourceEditor;

UCLASS()
class UQTMConnectLiveLinkSourceFactory : public ULiveLinkSourceFactory
{
public:

    GENERATED_BODY()

    virtual FText GetSourceDisplayName() const;
    virtual FText GetSourceTooltip() const;

    virtual TSharedPtr<SWidget> CreateSourceCreationPanel();
    virtual TSharedPtr<ILiveLinkSource> OnSourceCreationPanelClosed(bool bMakeSource);

    TSharedPtr<SQTMConnectLiveLinkSourceEditor> ActiveSourceEditor;
};