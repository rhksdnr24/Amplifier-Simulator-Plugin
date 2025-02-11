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
    apvts.addParameterListener(Amp_1_GainID, this);
}

Amplifer_Simulator_PluginAudioProcessor::~Amplifer_Simulator_PluginAudioProcessor()
{
    apvts.removeParameterListener(Amp_1_GainID, this);
}

juce::AudioProcessorValueTreeState::ParameterLayout Amplifer_Simulator_PluginAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID(Amp_1_GainID, 1), Amp_1_GainName, -24.0f, 24.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID(Amp_1_OutputID, 1), Amp_1_OutputName, -24.0f, 24.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID(Amp_1_PresenceID, 1), Amp_1_PresenceName, 0.5f, 1.5f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID(Amp_1_BassID, 1), Amp_1_BassName, 0.0f, 2.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID(Amp_1_MiddleID, 1), Amp_1_MiddleName, 0.0f, 2.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID(Amp_1_TrebleID, 1), Amp_1_TrebleName, 0.0f, 2.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID(Amp_1_OnOffSwitchID, 1),Amp_1_OnOffSwitchName, false));
    DBG("parameter made");
    return {params.begin(), params.end()};
}

void Amplifer_Simulator_PluginAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    updateParams();
}

void Amplifer_Simulator_PluginAudioProcessor::updateParams()
{
    _gain.setGainDecibels(*apvts.getRawParameterValue(Amp_1_GainID));
    _output.setGainDecibels(*apvts.getRawParameterValue(Amp_1_OutputID));
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
    float presenceEq = *apvts.getRawParameterValue(Amp_1_PresenceID);
    
    float centerFreqeuncy = 3000.0f + presenceEq * 500.0f;
    float qFactor = 0.6f + presenceEq * 0.05f;
    
    centerFreqeuncy = juce::jlimit(3000.0f, 6000.0f, centerFreqeuncy);
    qFactor = juce::jlimit(0.1f, 1.0f, qFactor);
    
    auto& presenceFilter = processorChain.get<presenceIndex>();
    *presenceFilter.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), centerFreqeuncy, qFactor, presenceEq);
}

void Amplifer_Simulator_PluginAudioProcessor::equalize()
{
    float bassGain = *apvts.getRawParameterValue(Amp_1_BassID);
    float middleGain = *apvts.getRawParameterValue(Amp_1_MiddleID);
    float trebleGain = *apvts.getRawParameterValue(Amp_1_TrebleID);
    
    bassGain = juce::jlimit(0.01f, 2.0f, bassGain);
    middleGain = juce::jlimit(0.01f, 2.0f, middleGain);
    trebleGain = juce::jlimit(0.01f, 2.0f, trebleGain);
    
    auto& bassFilter = processorChain.get<bassIndex>();
    *bassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), 150.0f, 0.6f, bassGain);
    
    auto& middleFilter = processorChain.get<middleIndex>();
    *middleFilter.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), 500.0f, 0.8f, middleGain);
    
    auto& trebleFilter = processorChain.get<trebleIndex>();
    *trebleFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), 3000.0f, 0.6f, trebleGain);
    
//    auto& bassFilter = processorChain.get<bassIndex>();
//    *bassFilter.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter (getSampleRate(), 100.0f, 0.6f, bass);
//
//    auto& midFilter = processorChain.get<midIndex>();
//    *midFilter.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter (getSampleRate(), 500.0f, 0.9f, mid);
//
//    auto& trebleFilter = processorChain.get<trebleIndex>();
//    *trebleFilter.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter (getSampleRate(), 5000.0f, 0.6f, treble);

    
}

//==============================================================================
void Amplifer_Simulator_PluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mSpec.maximumBlockSize = samplesPerBlock;
    mSpec.sampleRate = sampleRate;
    mSpec.numChannels = getTotalNumOutputChannels();

    _gain.setGainDecibels(*apvts.getRawParameterValue(Amp_1_GainID));
    

    _output.setGainDecibels(*apvts.getRawParameterValue(Amp_1_OutputID));

    mSpeakerModule.prepare(mSpec);
    mSpeakerModule.loadImpulseResponse(BinaryData::Acoustasonic_Mex3_48k_Ph_Qck_Std_wav, BinaryData::Acoustasonic_Mex3_48k_Ph_Qck_Std_wavSize, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, 0);
    
    _gain.prepare(mSpec);
    _gain.setRampDurationSeconds(0.02);
    
    presence();
    equalize();
    processorChain.prepare(mSpec);
    
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

    if (*apvts.getRawParameterValue(Amp_1_OnOffSwitchID))
    {
        juce::dsp::AudioBlock<float> inputBlock {buffer};
        _gain.setGainDecibels(*apvts.getRawParameterValue(Amp_1_GainID));
        _gain.process(juce::dsp::ProcessContextReplacing<float>(inputBlock));
        
        presence();
        equalize();
        
        juce::dsp::AudioBlock<float> processorChainBlock {buffer};
        processorChain.process(juce::dsp::ProcessContextReplacing<float>(processorChainBlock));
        
        juce::dsp::AudioBlock<float> outputBlock {buffer};
        _output.setGainDecibels(*apvts.getRawParameterValue(Amp_1_OutputID));
        _output.process(juce::dsp::ProcessContextReplacing<float>(outputBlock));
    }
    
}

//==============================================================================
bool Amplifer_Simulator_PluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Amplifer_Simulator_PluginAudioProcessor::createEditor()
{
    return new Amplifer_Simulator_PluginAudioProcessorEditor (*this);
//    return new juce::GenericAudioProcessorEditor(*this);
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
