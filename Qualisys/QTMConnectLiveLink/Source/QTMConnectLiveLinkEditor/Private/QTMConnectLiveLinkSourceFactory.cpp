// QTM Connect For Unreal. Copyright 2018-2022 Qualisys
//
#include "QTMConnectLiveLinkSourceFactory.h"
#include "QTMConnectLiveLinkSource.h"
#include "QTMConnectLiveLinkSourceEditor.h"

#include "ILiveLinkClient.h"
#include "Features/IModularFeatures.h"

#define LOCTEXT_NAMESPACE "QTMConnectLiveLinkSourceFactory"

FText UQTMConnectLiveLinkSourceFactory::GetSourceDisplayName() const
{
    return LOCTEXT("SourceDisplayName", "QTM Connect LiveLink");
}

FText UQTMConnectLiveLinkSourceFactory::GetSourceTooltip() const
{
    return LOCTEXT("SourceTooltip", "Creates a connection to QTM");
}

ULiveLinkSourceFactory::EMenuType UQTMConnectLiveLinkSourceFactory::GetMenuType() const
{
    return ULiveLinkSourceFactory::EMenuType::SubPanel;
}

TSharedPtr<SWidget> UQTMConnectLiveLinkSourceFactory::BuildCreationPanel(FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const
{
    return SNew(SQTMConnectLiveLinkSourceEditor)
        .OnPropertiesSelected(FQTMConnectLiveLinkSourceEditorPropertiesSelected::CreateUObject(this, &UQTMConnectLiveLinkSourceFactory::OnPropertiesSelected, OnLiveLinkSourceCreated));
}

TSharedPtr<ILiveLinkSource> UQTMConnectLiveLinkSourceFactory::CreateSource(const FString& ConnectionString) const
{
    QTMConnectLiveLinkSettings settings = QTMConnectLiveLinkSettings::FromString(ConnectionString);
    TSharedPtr<FQTMConnectLiveLinkSource> linkSource = MakeShareable(new FQTMConnectLiveLinkSource(settings));
    return linkSource;
}

void UQTMConnectLiveLinkSourceFactory::OnPropertiesSelected(QTMConnectLiveLinkSettings settings, FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const
{
    FString settingsString = settings.ToString();
    TSharedPtr<FQTMConnectLiveLinkSource> linkSource = MakeShareable(new FQTMConnectLiveLinkSource(settings));
    OnLiveLinkSourceCreated.ExecuteIfBound(linkSource, MoveTemp(settingsString));
}

#undef LOCTEXT_NAMESPACE