// QTM Connect For Unreal. Copyright 2018-2020 Qualisys
//
#pragma once

#include "QtmConnectLiveLinkSource.h"

#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"
#include "IMessageContext.h"
#include "MessageEndpoint.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Misc/Guid.h"
#include "Widgets/Input/SEditableTextBox.h"

DECLARE_DELEGATE_OneParam(FQTMConnectLiveLinkSourceEditorPropertiesSelected, QTMConnectLiveLinkSettings);

class QTMCONNECTLIVELINKEDITOR_API SQTMConnectLiveLinkSourceEditor : public SCompoundWidget
{
    SLATE_BEGIN_ARGS(SQTMConnectLiveLinkSourceEditor)
    {
    }

    SLATE_EVENT(FQTMConnectLiveLinkSourceEditorPropertiesSelected, OnPropertiesSelected)

    SLATE_END_ARGS()

    const unsigned short defaultPort = -1;

    SQTMConnectLiveLinkSourceEditor()
    {
        Port = defaultPort;
    };

    ~SQTMConnectLiveLinkSourceEditor();

    void Construct(const FArguments& Args);

    unsigned short GetPort() const
    {
        return Port.IsSet() ? Port.GetValue() : defaultPort;
    }

    FString GetIpAddress() const
    {
        return IpAddress.Get()->GetText().ToString();
    }

private:
    TOptional<unsigned short> Port;
    TOptional<unsigned short> OnGetPort() const
    {
        return Port;
    };

    void OnPortChanged(unsigned short InPortNumber)
    {
        Port = InPortNumber;
    };

    TSharedPtr<SEditableTextBox> IpAddress;

    FReply CreateSource() const;
    FQTMConnectLiveLinkSourceEditorPropertiesSelected OnPropertiesSelected;
};