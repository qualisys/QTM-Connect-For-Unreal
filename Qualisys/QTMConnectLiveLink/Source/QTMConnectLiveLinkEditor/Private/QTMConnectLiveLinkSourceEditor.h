// QTM Connect For Unreal. Copyright 2018-2019 Qualisys
//
#pragma once

#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"
#include "IMessageContext.h"
#include "MessageEndpoint.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Misc/Guid.h"
#include "Widgets/Input/SEditableTextBox.h"

class QTMCONNECTLIVELINKEDITOR_API SQTMConnectLiveLinkSourceEditor : public SCompoundWidget
{
    SLATE_BEGIN_ARGS(SQTMConnectLiveLinkSourceEditor)
    {
    }

    SLATE_END_ARGS()

    const unsigned short defaultPort = 9456;

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

};