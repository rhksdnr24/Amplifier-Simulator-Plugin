/*
  ==============================================================================

    AmpPage.cpp
    Created: 30 Jan 2025 11:56:07am
    Author:  새 주인

  ==============================================================================
*/

#include "AmpPage.h"

AmpPage::AmpPage(juce::AudioProcessorValueTreeState & apvts):
Amp_1(apvts, Amp_1_GainID, Amp_1_BassID, Amp_1_MiddleID, Amp_1_TrebleID, Amp_1_PresenceID, Amp_1_OutputID, Amp_1_ToggleID)
{
    addAndMakeVisible(Amp_1);
    Amp_1.setName(" ");
}

AmpPage::~AmpPage()
{
    
}

void AmpPage::paint(juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello \nMy name is \nAmpPage!", getLocalBounds(), juce::Justification::centred, 1);
}

void AmpPage::resized()
{
    Amp_1.setBounds(0, 0, Window_W, Window_H);
    DBG("Amp_1 Address: ");
}
