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
    
private:
    void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
};

/*
*/
class GainSliderLookAndFeel  : public juce::LookAndFeel_V4
{
public:
    GainSliderLookAndFeel();
    ~GainSliderLookAndFeel();
    
private:
    juce::Slider::SliderLayout getSliderLayout(juce::Slider& slider) override;
};

//==============================================================================
/*
*/
class ChannelMeter  : public juce::Component,
                      public juce::Button::Listener
{
public:
    ChannelMeter();
    ChannelMeter(ChannelInformation& infoToDisplay);
    ~ChannelMeter() override;

    void paint (juce::Graphics& g) override;
    void paintOverChildren(juce::Graphics& g) override;
    
    void resized() override;

private:
    void buttonClicked(juce::Button* button) override;
    
    ChannelInformation temp;
    
    ChannelInformation& displayedInformation;
    
    juce::Slider gainSlider;
    
    OnOffButton onOffButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelMeter)
};