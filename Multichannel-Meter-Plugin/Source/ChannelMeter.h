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
    
    juce::Label* createSliderTextBox(juce::Slider& slider) override;
};

//==============================================================================
/*
*/
class ChannelMeter  : public juce::Component,
                      public juce::Button::Listener,
                      public ChannelInformation::Listener,
                      public juce::Slider::Listener
{
public:
    ChannelMeter(ChannelInformation& infoToDisplay);
    ~ChannelMeter() override;

    void paint (juce::Graphics& g) override;
    void paintOverChildren(juce::Graphics& g) override;
    
    void resized() override;
    
private:
    void buttonClicked(juce::Button* button) override;
    
    void currentPeakChanged(ChannelInformation* informationChanged) override;
    
    void sliderValueChanged(juce::Slider* slider) override;
    
    void mouseDown(const juce::MouseEvent& event) override;
    
    void mouseDrag(const juce::MouseEvent& event) override;
    
    ChannelInformation& displayedInformation;
    
    GainSliderLookAndFeel gainSliderLAF;
    juce::Slider gainSlider;
    
    OnOffButton onOffButton;
    
    juce::Label channelNameLabel;
    
    juce::Label peakLevelLabel;
    
    juce::ComponentDragger dragger;
    
    juce::ComponentBoundsConstrainer constrainer;
    
    juce::ResizableCornerComponent resizer;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelMeter)
};
