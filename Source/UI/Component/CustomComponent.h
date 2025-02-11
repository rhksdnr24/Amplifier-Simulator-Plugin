/*
  ==============================================================================

    CustomComponent.h
    Created: 30 Jan 2025 12:09:50pm
    Author:  새 주인

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Parameters/Globals.h"
static constexpr float fontHeight { 15.0f };

// Slider로 노브를 조절하는 객체
class SliderWithLabel : public juce::Component
{
public:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using SliderStyle = juce::Slider::SliderStyle;
    
    SliderWithLabel(juce::AudioProcessorValueTreeState & apvts, juce::String labelName, juce::String paramId, const int width, const int height, SliderStyle style = SliderStyle::RotaryHorizontalVerticalDrag);
    void resized() override;
    
private:
    static constexpr int textBoxWidth { 48 };
    static constexpr int textBoxHeight { 20 };
    int sliderWidth { 0 };
    int sliderHeight { 0 };
    juce::Slider slider;
    juce::Label label;
    std::unique_ptr<SliderAttachment> sliderAttachment;
};

class CustomToggle : public juce::Component
{
public:
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

    CustomToggle(juce::AudioProcessorValueTreeState& apvts, juce::String labelName, juce::String paramId, int width, int height);

    void resized() override;

private:
    void updateButtonState();

    juce::ToggleButton toggleButton;
    juce::Label label;
    std::unique_ptr<ButtonAttachment> toggleAttachment;

    int toggleWidth;
    int toggleHeight;
};

// Switch로 On / Off를 제어하는 클래스
//class CustomToggle : public juce::Component
//{
//public:
//    using ToggleAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
////    using SliderStyle = juce::Slider::SliderStyle;
//
//    CustomToggle(juce::AudioProcessorValueTreeState & apvts, juce::String labelName, juce::String paramId, const int width, const int height);
//    void resized() override;
//    
//private:
//    static constexpr int textBoxWidth { 48 };
//    static constexpr int textBoxHeight { 20 };
//    int toggleWidth { 0 };
//    int toggleHeight { 0 };
//    juce::ToggleButton toggle;
//    juce::Label label;
//    std::unique_ptr<ToggleAttachment> toggleAttachment;
//};

class CustomComponent : public juce::Component
{
public:
    CustomComponent();
    ~CustomComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void setName (juce::String n) { name = n; }
    void setBoundsColour (juce::Colour c) { boundsColour = c; }

private:
    juce::String name { "" };
    juce::Colour boundsColour { juce::Colours::white };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomComponent)

};
