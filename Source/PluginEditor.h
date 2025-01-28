/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Amplifer_Simulator_PluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Amplifer_Simulator_PluginAudioProcessorEditor (Amplifer_Simulator_PluginAudioProcessor&);
    ~Amplifer_Simulator_PluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Amplifer_Simulator_PluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Amplifer_Simulator_PluginAudioProcessorEditor)
};
