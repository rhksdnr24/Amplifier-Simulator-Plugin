/*
  ==============================================================================

    PostFxPage.h
    Created: 30 Jan 2025 11:56:47am
    Author:  새 주인

  ==============================================================================
*/

#pragma once
#include "CustomPage.h"

class PostFxPage : public CustomPage
{
public:
    PostFxPage(juce::AudioProcessorValueTreeState & apvts);
    ~PostFxPage();
    void resized() override;
    void paint(juce::Graphics & g) override;
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PostFxPage)
};
