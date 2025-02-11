/*
  ==============================================================================

    Amp_1_Component.cpp
    Created: 10 Feb 2025 1:16:39pm
    Author:  새 주인

  ==============================================================================
*/

#include "Amp_1_Component.h"

Amp_1_Component::Amp_1_Component(juce::AudioProcessorValueTreeState& apvts, juce::String gainId, juce::String bassId, juce::String middleId, juce::String trebleId, juce::String presenceId, juce::String outputId, juce::String toggleId)
:gain(apvts, Amp_1_GainName, gainId, Amp_Nobe_Size_W, Amp_Nobe_Size_H)
,bass(apvts, Amp_1_BassName, bassId, Amp_Nobe_Size_W, Amp_Nobe_Size_H)
,middle(apvts, Amp_1_MiddleName, middleId, Amp_Nobe_Size_W, Amp_Nobe_Size_H)
,treble(apvts, Amp_1_TrebleName, trebleId, Amp_Nobe_Size_W, Amp_Nobe_Size_H)
,presence(apvts, Amp_1_PresenceName, presenceId, Amp_Nobe_Size_W, Amp_Nobe_Size_H)
,output(apvts, Amp_1_OutputName, outputId, Amp_Nobe_Size_W, Amp_Nobe_Size_H)
,onOffSwitch(apvts, Amp_1_OnOffSwitchName, Amp_1_OnOffSwitchID, Amp_Switch_Size_W, Amp_Switch_Size_H)


{
    DBG("Amp_1_Component constructor");

    addAndMakeVisible(gain);
    addAndMakeVisible(bass);
    addAndMakeVisible(middle);
    addAndMakeVisible(treble);
    addAndMakeVisible(presence);
    addAndMakeVisible(output);
    addAndMakeVisible(onOffSwitch);
}
Amp_1_Component::~Amp_1_Component()
{
    
}

void Amp_1_Component::resized()
{
    DBG("Amp Resized");
    gain.setBounds(Amp_Nobe_Pos_W, Amp_Nobe_Pos_H, Amp_Nobe_Size_W, Amp_Nobe_Size_H);
    bass.setBounds(Amp_Nobe_Pos_W + 100, Amp_Nobe_Pos_H, Amp_Nobe_Size_W, Amp_Nobe_Size_H);
    middle.setBounds(Amp_Nobe_Pos_W + 200, Amp_Nobe_Pos_H, Amp_Nobe_Size_W, Amp_Nobe_Size_H);
    treble.setBounds(Amp_Nobe_Pos_W + 300, Amp_Nobe_Pos_H, Amp_Nobe_Size_W, Amp_Nobe_Size_H);
    presence.setBounds(Amp_Nobe_Pos_W + 400, Amp_Nobe_Pos_H, Amp_Nobe_Size_W, Amp_Nobe_Size_H);
    output.setBounds(Amp_Nobe_Pos_W + 500, Amp_Nobe_Pos_H, Amp_Nobe_Size_W, Amp_Nobe_Size_H);
    onOffSwitch.setBounds(Amp_Switch_Pos_W, Amp_Switch_Pos_H, Amp_Nobe_Size_W, Amp_Nobe_Size_H);
}

