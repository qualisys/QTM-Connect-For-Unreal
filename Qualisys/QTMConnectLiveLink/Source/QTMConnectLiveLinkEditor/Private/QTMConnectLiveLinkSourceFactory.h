// QTM Connect For Unreal. Copyright 2018-2022 Qualisys
//
#pragma once

#include "LiveLinkSourceFactory.h"
#include "QTMConnectLiveLinkSource.h"
#include "QTMConnectLiveLinkSourceFactory.generated.h"

class SQTMConnectLiveLinkSourceEditor;

UCLASS()
class UQTMConnectLiveLinkSourceFactory : public ULiveLinkSourceFactory
{
public:

    GENERATED_BODY()

    virtual FText GetSourceDisplayName() const override;
    virtual FText GetSourceTooltip() const override;
    virtual EMenuType GetMenuType() const override;
    virtual TSharedPtr<SWidget> BuildCreationPanel(FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const override;
    virtual TSharedPtr<ILiveLinkSource> CreateSource(const FString& ConnectionString) const override;

private:
    void OnPropertiesSelected(QTMConnectLiveLinkSettings settings, FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const;
};