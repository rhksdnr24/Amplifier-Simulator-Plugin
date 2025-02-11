/*
  ==============================================================================

    AmpPage.h
    Created: 30 Jan 2025 11:56:07am
    Author:  새 주인

  ==============================================================================
*/

#pragma once
#include "CustomPage.h"
#include "Component/Amp_1_Component.h"
#include "../Parameters/Globals.h"

class AmpPage : public CustomPage
{
public:
    AmpPage(juce::AudioProcessorValueTreeState & apvts);
    ~AmpPage();
    void resized() override;
    void paint(juce::Graphics & g) override;
private:
    
    Amp_1_Component Amp_1;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AmpPage)
};
