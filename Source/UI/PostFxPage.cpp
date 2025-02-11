/*
  ==============================================================================

    PostFxPage.cpp
    Created: 30 Jan 2025 11:56:47am
    Author:  새 주인

  ==============================================================================
*/

#include "PostFxPage.h"

PostFxPage::PostFxPage(juce::AudioProcessorValueTreeState & apvts)
{
    
}

PostFxPage::~PostFxPage()
{
    
}

void PostFxPage::paint(juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello \nMy name is \nPostFxPage!", getLocalBounds(), juce::Justification::centred, 1);
}

void PostFxPage::resized()
{
    
}
