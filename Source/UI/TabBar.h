/*
  ==============================================================================

    TabBar.h
    Created: 9 Feb 2025 9:11:43am
    Author:  새 주인

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AmpPage.h"
#include "PostFxPage.h"
#include "PreFxPage.h"
class CustomTabButton : public juce::Component
{
public:
    CustomTabButton (bool isRunningComponentTransformsDemo);
    
    void paint (juce::Graphics& g) override;

//    void mouseDown (const juce::MouseEvent&) override;

private:
    bool runningComponentTransformsDemo;
    std::unique_ptr<juce::BubbleMessageComponent> bubbleMessage;
};

class CustomBar : public juce::TabbedComponent
{
public:
    CustomBar(juce::AudioProcessorValueTreeState& apvts);
    ~CustomBar();
    
    void resized();
private:
    PreFxPage preFx;
    AmpPage amp;
    PostFxPage postFx;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomBar)
};
