// QTM Connect For Unreal. Copyright 2018-2020 Qualisys
//
#include "QTMConnectLiveLinkSourceEditor.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SCheckBox.h"

#define LOCTEXT_NAMESPACE "QTMConnectLiveLinkSourceEditor"

SQTMConnectLiveLinkSourceEditor::~SQTMConnectLiveLinkSourceEditor()
{
}

void SQTMConnectLiveLinkSourceEditor::Construct(const FArguments& Args)
{
    OnPropertiesSelected = Args._OnPropertiesSelected;

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
                    .Text(LOCTEXT("AutoDiscover", "Auto Discover"))
                ]
                + SHorizontalBox::Slot()
                .HAlign(HAlign_Fill)
                .FillWidth(0.5f)
                [
                    SAssignNew(AutoDiscoverCB, SCheckBox)
                    .IsChecked(ECheckBoxState::Checked)
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
                    .Text(LOCTEXT("QTMIpAddress", "QTM Server IP Address"))
                ]
                + SHorizontalBox::Slot()
                .HAlign(HAlign_Fill)
                .FillWidth(0.5f)
                [
                    SAssignNew(IpAddress, SEditableTextBox)
                    .Text(LOCTEXT("DefaultQTMIpAddress", "127.0.0.1"))
                    .IsEnabled(&SQTMConnectLiveLinkSourceEditor::IsAutoConnect)
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
                    .Text(LOCTEXT("Stream3d", "Stream Markers"))
                ]
                + SHorizontalBox::Slot()
                .HAlign(HAlign_Fill)
                .FillWidth(0.5f)
                [
                    SAssignNew(Stream3dCB, SCheckBox)
                    .IsChecked(ECheckBoxState::Unchecked)
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
                    .Text(LOCTEXT("Stream6d", "Stream Rigid Bodies"))
                ]
                + SHorizontalBox::Slot()
                .HAlign(HAlign_Fill)
                .FillWidth(0.5f)
                [
                    SAssignNew(Stream6dCB, SCheckBox)
                    .IsChecked(ECheckBoxState::Checked)
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
                    .Text(LOCTEXT("StreamSkeleton", "Stream Skeletons"))
                ]
                + SHorizontalBox::Slot()
                .HAlign(HAlign_Fill)
                .FillWidth(0.5f)
                [
                    SAssignNew(StreamSkeletonCB, SCheckBox)
                    .IsChecked(ECheckBoxState::Checked)
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
                    .Text(LOCTEXT("StreamForce", "Stream Force"))
                ]
            + SHorizontalBox::Slot()
                .HAlign(HAlign_Fill)
                .FillWidth(0.5f)
                [
                    SAssignNew(StreamForceCB, SCheckBox)
                    .IsChecked(ECheckBoxState::Unchecked)
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
                    .Text(LOCTEXT("StreamRate", "Stream Rate"))
                ]
            + SHorizontalBox::Slot()
                .HAlign(HAlign_Fill)
                .FillWidth(0.5f)
                [
                    SAssignNew(StreamRatesTB, STextComboBox)
                    .OptionsSource(&StreamRates)
                    .InitiallySelectedItem(*StreamRates.begin())
                    .OnSelectionChanged_Lambda(
                        [&](TSharedPtr<FString> text, ESelectInfo::Type)
                        {
                            bool allFrames = (text == *StreamRates.begin());
                            FrequencyValueText->SetEnabled(!allFrames);
                            FrequencyValueTB->SetEnabled(!allFrames);
                            FrequencyValueText->SetText(allFrames ? FText::FromString("Frequency") : FText::FromString(*text));
                        }
                    )
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
                    SAssignNew(FrequencyValueText, SEditableText)
                    .Text(LOCTEXT("Frequency", "Frequency"))
                ]
                + SHorizontalBox::Slot()
                .HAlign(HAlign_Fill)
                .FillWidth(0.5f)
                [
                    SAssignNew(FrequencyValueTB, SEditableTextBox)
                    .Text(LOCTEXT("0", "0"))
                    .OnTextChanged_Lambda(
                        [&](const FText& Val)
                        {
                            if (!Val.IsNumeric())
                            {
                                FrequencyValueTB->SetText(FText::FromString(Val.ToString().LeftChop(1)));//This gets rid of the last character in the text since it made it non-numeric.
                            }
                        }
                    )
                ]
            ]

            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(3.0f)
            [
                SNew(SButton)
                .Text(LOCTEXT("Create", "Create"))
                .OnClicked(this, &SQTMConnectLiveLinkSourceEditor::CreateSource)
            ]
        ]
    ];
    FrequencyValueText->SetEnabled(false);
    FrequencyValueTB->SetEnabled(false);
}

FReply SQTMConnectLiveLinkSourceEditor::CreateSource() const
{
    QTMConnectLiveLinkSettings settings;
    settings.IpAddress = this->GetIpAddress();
    settings.AutoDiscover = this->GetAutoDiscover();
    settings.Stream3d = this->GetStream3d();
    settings.Stream6d = this->GetStream6d();
    settings.StreamSkeleton = this->GetStreamSkeleton();
    settings.StreamForce = this->GetStreamForce();
    settings.StreamRate = this->GetStreamRate();
    settings.FrequencyValue = this->GetFrequencyValue();
    OnPropertiesSelected.ExecuteIfBound(settings);
    return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
