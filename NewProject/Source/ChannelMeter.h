/*
  ==============================================================================

    ChannelMeter.h
    Created: 4 Aug 2020 10:54:29am
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ChannelInformation.h"

/*
*/
class OnOffButton  : public juce::Button
{
public:
    OnOffButton();
    ~OnOffButton();
    
    void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
};

//==============================================================================
/*
*/
class ChannelMeter  : public juce::Component
{
public:
    ChannelMeter();
    ChannelMeter(ChannelInformation& infoToDisplay);
    ~ChannelMeter() override;

    void paint (juce::Graphics& g) override;
    void paintOverChildren(juce::Graphics& g) override;
    
    void resized() override;

private:
    ChannelInformation temp;
    
    ChannelInformation& displayedInformation;
    
    juce::Slider gainSlider;
    
    OnOffButton onOffButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelMeter)
};
