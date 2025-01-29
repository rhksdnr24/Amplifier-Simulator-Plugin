/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Amplifer_Simulator_PluginAudioProcessor::Amplifer_Simulator_PluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
//                        .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
//                        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
), apvts(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    apvts.addParameterListener(inputID, this);
}

Amplifer_Simulator_PluginAudioProcessor::~Amplifer_Simulator_PluginAudioProcessor()
{
    apvts.removeParameterListener(inputID, this);
}

juce::AudioProcessorValueTreeState::ParameterLayout Amplifer_Simulator_PluginAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID(inputID, 1), inputName, -24.0f, 24.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID(outputID, 1), outputName, -24.0f, 24.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID(presenceID, 1), presenceName, 0.5f, 1.5f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID(bassID, 1), bassName, 0.0f, 2.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID(middleID, 1), middleName, 0.0f, 2.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID(trebleID, 1), trebleName, 0.0f, 2.0f, 1.0f));

    
    return {params.begin(), params.end()};
}

void Amplifer_Simulator_PluginAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    updateParams();
}

void Amplifer_Simulator_PluginAudioProcessor::updateParams()
{
    _gain.setGainDecibels(*apvts.getRawParameterValue(inputID));
    _output.setGainDecibels(*apvts.getRawParameterValue(outputID));
}

//==============================================================================
const juce::String Amplifer_Simulator_PluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Amplifer_Simulator_PluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Amplifer_Simulator_PluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Amplifer_Simulator_PluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Amplifer_Simulator_PluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Amplifer_Simulator_PluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Amplifer_Simulator_PluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Amplifer_Simulator_PluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Amplifer_Simulator_PluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void Amplifer_Simulator_PluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void Amplifer_Simulator_PluginAudioProcessor::presence()
{
        
}

void Amplifer_Simulator_PluginAudioProcessor::equalize()
{
        
}

//==============================================================================
void Amplifer_Simulator_PluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mSpec.maximumBlockSize = samplesPerBlock;
    mSpec.sampleRate = sampleRate;
    mSpec.numChannels = getTotalNumOutputChannels();

    updateParams();
    
    mSpeakerModule.prepare(mSpec);
    mSpeakerModule.loadImpulseResponse(BinaryData::Acoustasonic_Mex3_48k_Ph_Qck_Std_wav, BinaryData::Acoustasonic_Mex3_48k_Ph_Qck_Std_wavSize, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, 0);
    
    _gain.prepare(mSpec);
    _gain.setRampDurationSeconds(0.02);
    
    presence();
    equalize();
    
    
}

void Amplifer_Simulator_PluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Amplifer_Simulator_PluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Amplifer_Simulator_PluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    updateParams();

    juce::dsp::AudioBlock<float> block {buffer};

    _gain.process(juce::dsp::ProcessContextReplacing<float>(block));
    _output.process(juce::dsp::ProcessContextReplacing<float>(block));

    
    
//    juce::dsp::AudioBlock<float> _inputblock {buffer};
//    juce::dsp::AudioBlock<float> _outputblock {buffer};
//
//    _input.process(juce::dsp::ProcessContextReplacing<float>(_inputblock));
//    _output.process(juce::dsp::ProcessContextReplacing<float>(_outputblock));

}

//==============================================================================
bool Amplifer_Simulator_PluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Amplifer_Simulator_PluginAudioProcessor::createEditor()
{
//    return new Amplifer_Simulator_PluginAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void Amplifer_Simulator_PluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Amplifer_Simulator_PluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Amplifer_Simulator_PluginAudioProcessor();
}
