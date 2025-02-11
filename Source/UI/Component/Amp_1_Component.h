/*
  ==============================================================================

    Amp_1_Component.h
    Created: 10 Feb 2025 1:16:39pm
    Author:  새 주인
    gain, processorchain, output, on / off
  ==============================================================================
*/

#pragma once
#include "CustomComponent.h"
#include "../../Parameters/Globals.h"

class Amp_1_Component : public CustomComponent
{
public:
    Amp_1_Component(juce::AudioProcessorValueTreeState& apvts, juce::String gainId, juce::String bassId, juce::String middleId, juce::String trebleId, juce::String presenceId, juce::String outputId, juce::String toggleId);
    ~Amp_1_Component();
    
    void resized();
private:
    SliderWithLabel gain;
    SliderWithLabel bass;
    SliderWithLabel middle;
    SliderWithLabel treble;
    SliderWithLabel presence;
    SliderWithLabel output;
    CustomToggle onOffSwitch;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Amp_1_Component)
};
