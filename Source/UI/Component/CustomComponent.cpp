/*
  ==============================================================================

    CustomComponent.cpp
    Created: 30 Jan 2025 12:09:50pm
    Author:  새 주인

  ==============================================================================
*/

#include "CustomComponent.h"
using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
using SliderStyle = juce::Slider::SliderStyle;

SliderWithLabel::SliderWithLabel (juce::AudioProcessorValueTreeState& apvts, juce::String labelName, juce::String paramId, const int width, const int height, SliderStyle style)
{
    sliderWidth = width;
    sliderHeight = height;
    
    slider.setSliderStyle (style);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, textBoxWidth, textBoxHeight);
    addAndMakeVisible (slider);
    
    label.setFont (fontHeight);
    label.setText (labelName, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label);
    
    sliderAttachment = std::make_unique<SliderAttachment>(apvts,  paramId,  slider);
}

void SliderWithLabel::resized()
{
    jassert (sliderWidth > 0);
    jassert (sliderHeight > 0);
    
    label.setBounds (0, 0, sliderWidth, Amp_Nobe_Label_H);
    slider.setBounds (0, 0 + Amp_Nobe_Label_2_Slider, sliderWidth, sliderHeight);
}


CustomToggle::CustomToggle(juce::AudioProcessorValueTreeState& apvts, juce::String labelName, juce::String paramId, int width, int height)
{
    toggleWidth = width;
    toggleHeight = height;

    // 🔹 Label 설정
    label.setFont(15.0f);
    label.setText(labelName, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

    // 🔹 ToggleButton 설정
    toggleButton.setButtonText("OFF");
    toggleButton.setClickingTogglesState(true); // ✅ 클릭 시 ON/OFF 전환 가능
    toggleButton.onClick = [this]() { updateButtonState(); }; // ✅ 클릭 시 UI 업데이트
    addAndMakeVisible(toggleButton);

    // 🔹 AudioProcessorValueTreeState와 연결
    toggleAttachment = std::make_unique<ButtonAttachment>(apvts, paramId, toggleButton);
}

void CustomToggle::resized()
{
    label.setBounds (0, 0, toggleWidth, Amp_Switch_Label_H);
    toggleButton.setBounds (0, 0 + Amp_Switch_Label_2_Toggle, toggleWidth, toggleHeight);
}

void CustomToggle::updateButtonState()
{
    // ✅ 버튼 상태에 따라 텍스트 변경
    toggleButton.setButtonText(toggleButton.getToggleState() ? "ON" : "OFF");
}



CustomComponent::CustomComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

CustomComponent::~CustomComponent()
{
}

void CustomComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    auto bounds = getLocalBounds();
    g.setColour (boundsColour);
    g.drawRoundedRectangle (bounds.toFloat().reduced (10.0f), 5.0f, 2.0f);
    
    g.setColour (juce::Colours::yellow);
    g.setFont (fontHeight);
    g.setFont (g.getCurrentFont().boldened());
    
    jassert (name.isNotEmpty());
    g.drawText (name, 20, 15, 100, 25, juce::Justification::left);
}

void CustomComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
