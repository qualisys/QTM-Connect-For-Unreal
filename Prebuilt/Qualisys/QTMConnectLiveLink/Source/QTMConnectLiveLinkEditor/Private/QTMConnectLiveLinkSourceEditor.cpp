// QTM Connect For Unreal. Copyright 2018-2019 Qualisys
//
#include "QTMConnectLiveLinkSourceEditor.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "Widgets/Input/SEditableTextBox.h"

#define LOCTEXT_NAMESPACE "QTMConnectLiveLinkSourceEditor"

SQTMConnectLiveLinkSourceEditor::~SQTMConnectLiveLinkSourceEditor()
{
}

void SQTMConnectLiveLinkSourceEditor::Construct(const FArguments& Args)
{
    ChildSlot
    [
        SNew(SBox)
        .WidthOverride(250)
        .HeightOverride(220)
        [
            SNew(SVerticalBox)
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(3.0f)
            [
                SNew(SHorizontalBox)
                + SHorizontalBox::Slot()
                .HAlign(HAlign_Left)
                .FillWidth(0.5f)
                [
                    SNew(STextBlock)
                    .Text(LOCTEXT("QTMIpAddress", "QTM Server IP Address"))
                ]
                + SHorizontalBox::Slot()
                .HAlign(HAlign_Fill)
                .FillWidth(0.5f)
                [
                    SAssignNew(IpAddress, SEditableTextBox).Text(LOCTEXT("DefaultQTMIpAddress", "127.0.0.1"))
                ]
            ]
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(3.0f)
            [
                SNew(SHorizontalBox)
                + SHorizontalBox::Slot()
                .HAlign(HAlign_Left)
                .FillWidth(0.5f)
                [
                    SNew(STextBlock)
                    .Text(LOCTEXT("QTMPort", "Udp Port"))
                ]
                + SHorizontalBox::Slot()
                .HAlign(HAlign_Fill)
                .FillWidth(0.5f)
                [
                    SNew(SNumericEntryBox<unsigned short>)
                    .Value(this, &SQTMConnectLiveLinkSourceEditor::OnGetPort)
                    .OnValueChanged(this, &SQTMConnectLiveLinkSourceEditor::OnPortChanged)
                ]
            ]
        ]
    ];
}

#undef LOCTEXT_NAMESPACE