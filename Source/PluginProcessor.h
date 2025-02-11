/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Parameters/Globals.h"

//==============================================================================
/**
*/
class Amplifer_Simulator_PluginAudioProcessor  : public juce::AudioProcessor,
public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    Amplifer_Simulator_PluginAudioProcessor();
    ~Amplifer_Simulator_PluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void updateParams();
    void prepareParams();
    void processParameters(juce::dsp::AudioBlock<float> audioBlock);
    void updatePresenceSettings();
    void updateEqualizeSettings();
    void prepareDSPModules();
    void updateGainSettings();
    bool isSwitchOn(juce::String ID);


    juce::AudioProcessorValueTreeState apvts;
    juce::dsp::Convolution mSpeakerModule;
private:
    enum
    {
        presenceIndex,
        bassIndex,
        middleIndex,
        trebleIndex
    };

    using IIRFilter = juce::dsp::IIR::Filter<float>;
    using IIRCoefs = juce::dsp::IIR::Coefficients<float>;

    juce::dsp::Gain<float> _gain;
    
    juce::dsp::ProcessorChain<juce::dsp::ProcessorDuplicator<IIRFilter, IIRCoefs>,
    juce::dsp::ProcessorDuplicator<IIRFilter, IIRCoefs>,
    juce::dsp::ProcessorDuplicator<IIRFilter, IIRCoefs>,
    juce::dsp::ProcessorDuplicator<IIRFilter, IIRCoefs>> processorChain;

    juce::dsp::Gain<float> _output;

    juce::dsp::ProcessSpec mSpec;

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged(const juce::String& parameterID, float newValue) override;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Amplifer_Simulator_PluginAudioProcessor)
    
};
