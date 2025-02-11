/*
  ==============================================================================

    TabBar.cpp
    Created: 9 Feb 2025 9:11:43am
    Author:  새 주인

  ==============================================================================
*/

#include "TabBar.h"

CustomTabButton::CustomTabButton(bool isRunningComponentTransformsDemo)
:runningComponentTransformsDemo (isRunningComponentTransformsDemo)
{
    setSize(20, 20);
}


void CustomTabButton::paint (juce::Graphics& g)
{
}

CustomBar::CustomBar(juce::AudioProcessorValueTreeState& apvts)
: juce::TabbedComponent (juce::TabbedButtonBar::TabsAtTop)
, preFx(apvts)
, amp(apvts)
, postFx(apvts)
{
    
    auto colour = findColour (juce::ResizableWindow::backgroundColourId);

    addTab("PreFx", colour, &preFx, true);
    addTab("Amp", colour, &amp, true);
    addTab("PostFx", colour, &postFx, true);

}

CustomBar::~CustomBar()
{
    
}
void CustomBar::resized()
{
    TabbedComponent::resized();
}
