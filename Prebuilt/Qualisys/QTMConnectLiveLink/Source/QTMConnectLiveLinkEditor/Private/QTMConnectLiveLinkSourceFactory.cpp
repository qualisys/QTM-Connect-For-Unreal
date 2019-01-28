// QTM Connect For Unreal. Copyright 2018-2019 Qualisys
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

TSharedPtr<SWidget> UQTMConnectLiveLinkSourceFactory::CreateSourceCreationPanel()
{
    if (!ActiveSourceEditor.IsValid())
    {
        SAssignNew(ActiveSourceEditor, SQTMConnectLiveLinkSourceEditor);
    }
    return ActiveSourceEditor;
}

TSharedPtr<ILiveLinkSource> UQTMConnectLiveLinkSourceFactory::OnSourceCreationPanelClosed(bool bMakeSource)
{
    TSharedPtr<FQTMConnectLiveLinkSource> NewSource = nullptr;

    if (bMakeSource && ActiveSourceEditor.IsValid())
    {
        QTMConnectLiveLinkSettings settings;
        settings.IpAddress = ActiveSourceEditor->GetIpAddress();
        settings.Port = ActiveSourceEditor->GetPort();

        NewSource = MakeShared<FQTMConnectLiveLinkSource>(settings);
    }

    ActiveSourceEditor = nullptr;
    return NewSource;
}

#undef LOCTEXT_NAMESPACE