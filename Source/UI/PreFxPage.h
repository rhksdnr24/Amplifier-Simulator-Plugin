/*
  ==============================================================================

    PreFxPage.h
    Created: 30 Jan 2025 11:56:30am
    Author:  새 주인

  ==============================================================================
*/

#pragma once
#include "CustomPage.h"

class PreFxPage : public CustomPage
{
public:
    PreFxPage(juce::AudioProcessorValueTreeState & apvts);
    ~PreFxPage();
    void resized() override;
    void paint(juce::Graphics & g) override;
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PreFxPage)
};
