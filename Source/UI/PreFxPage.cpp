/*
  ==============================================================================

    PreFxPage.cpp
    Created: 30 Jan 2025 11:56:30am
    Author:  새 주인

  ==============================================================================
*/

#include "PreFxPage.h"
PreFxPage::PreFxPage(juce::AudioProcessorValueTreeState & apvts)
{
    
}

PreFxPage::~PreFxPage()
{
    
}

void PreFxPage::paint(juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello \nMy name is \nPreFxPage!", getLocalBounds(), juce::Justification::centred, 1);
}

void PreFxPage::resized()
{
    
}
