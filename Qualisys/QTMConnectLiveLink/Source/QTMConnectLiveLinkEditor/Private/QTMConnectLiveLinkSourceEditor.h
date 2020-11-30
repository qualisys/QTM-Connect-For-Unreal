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
#include "Widgets/Input/SCheckBox.h"

DECLARE_DELEGATE_OneParam(FQTMConnectLiveLinkSourceEditorPropertiesSelected, QTMConnectLiveLinkSettings);

class QTMCONNECTLIVELINKEDITOR_API SQTMConnectLiveLinkSourceEditor : public SCompoundWidget
{
    SLATE_BEGIN_ARGS(SQTMConnectLiveLinkSourceEditor)
    {
    }

    SLATE_EVENT(FQTMConnectLiveLinkSourceEditorPropertiesSelected, OnPropertiesSelected)

    SLATE_END_ARGS()

    SQTMConnectLiveLinkSourceEditor()
    {
    };

    ~SQTMConnectLiveLinkSourceEditor();

    void Construct(const FArguments& Args);

    FString GetIpAddress() const
    {
        return IpAddress.Get()->GetText().ToString();
    }

    bool GetAutoDiscover() const
    {
        return IsAutoConnect();
    }

    bool GetStream3d() const
    {
        return IsStream3d();
    }

    bool GetStream6d() const
    {
        return IsStream6d();
    }

    bool GetStreamSkeleton() const
    {
        return IsStreamSkeleton();
    }


private:
    TSharedPtr<SEditableTextBox> IpAddress;
    TSharedPtr<SCheckBox> AutoDiscoverCB;
    TSharedPtr<SCheckBox> Stream3dCB;
    TSharedPtr<SCheckBox> Stream6dCB;
    TSharedPtr<SCheckBox> StreamSkeletonCB;

    bool IsAutoConnect() const
    {
        return AutoDiscoverCB->IsChecked();
    }

    bool IsStream3d() const
    {
        return Stream3dCB->IsChecked();
    }

    bool IsStream6d() const
    {
        return Stream6dCB->IsChecked();
    }

    bool IsStreamSkeleton() const
    {
        return StreamSkeletonCB->IsChecked();
    }

    FReply CreateSource() const;
    FQTMConnectLiveLinkSourceEditorPropertiesSelected OnPropertiesSelected;
};