/*
  ==============================================================================

    ChannelMeter.cpp
    Created: 4 Aug 2020 10:54:29am
    Author:  Max Walley

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChannelMeter.h"

OnOffButton::OnOffButton()  : juce::Button("")
{
    setClickingTogglesState(true);
    setToggleState(true, juce::NotificationType::dontSendNotification);
}

OnOffButton::~OnOffButton()
{
    
}

void OnOffButton::paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    if(getToggleState())
    {
        g.setColour(juce::Colours::silver);
    }
    else
    {
        g.setColour(juce::Colours::black);
    }
    
    juce::Path newPath;
    
    newPath.addArc(getWidth() / 6, getHeight() / 6, getWidth() / 3 * 2, getHeight() / 3 * 2, juce::float_Pi * 0.25, juce::float_Pi * 1.75, true);
    
    g.strokePath(newPath, juce::PathStrokeType(1.5));
    
    g.drawLine(getWidth() / 2 - 1, getHeight() / 8 , getWidth() / 2 - 1, getHeight() / 2, 1.5);
}

GainSliderLookAndFeel::GainSliderLookAndFeel()
{
    
}

GainSliderLookAndFeel::~GainSliderLookAndFeel()
{
    
}
    
juce::Slider::SliderLayout GainSliderLookAndFeel::getSliderLayout(juce::Slider& slider)
{
    juce::Slider::SliderLayout newLayout;
    
    int sliderHeightFifth = slider.getHeight() / 5;
    
    newLayout.sliderBounds = juce::Rectangle<int> (0, 10, slider.getWidth(), (sliderHeightFifth * 4) - 18);
    
    newLayout.textBoxBounds = juce::Rectangle<int> (0, sliderHeightFifth * 4, slider.getWidth(), sliderHeightFifth);
    
    return newLayout;
}

juce::Label* GainSliderLookAndFeel::createSliderTextBox(juce::Slider& slider)
{
    std::unique_ptr<juce::Label> sliderLabel = std::make_unique<juce::Label>();
    
    sliderLabel->setFont(juce::Font(10));
    
    sliderLabel->setColour(juce::Label::textColourId, juce::Colours::black);
    
    return sliderLabel.release();
}

//==============================================================================
ChannelMeter::ChannelMeter() : displayedInformation(temp)
{
    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(juce::Slider::LinearVertical);
    //gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 0, 0);
    gainSlider.setLookAndFeel(&gainSliderLAF);
    
    addAndMakeVisible(onOffButton);
    onOffButton.addListener(this);
};

ChannelMeter::ChannelMeter(ChannelInformation& infoToDisplay)  : displayedInformation(infoToDisplay)
{
    addAndMakeVisible(gainSlider);
    addAndMakeVisible(onOffButton);
}

ChannelMeter::~ChannelMeter()
{
    
}

void ChannelMeter::paint (juce::Graphics& g)
{
    
}

void ChannelMeter::paintOverChildren (juce::Graphics& g)
{
    g.setColour(juce::Colours::silver);
    
    g.drawRect(0, 0, getWidth(), getHeight(), 2.0);
    
    g.drawLine(getWidth() / 5 * 4, 0, getWidth() / 5 * 4, getHeight());
    
    g.drawLine(0, getHeight() / 5 * 4, getWidth(), getHeight() / 5 * 4);
    
    g.drawLine(getWidth() / 5, getHeight() / 5 * 4, getWidth() / 5, getHeight());
}

void ChannelMeter::resized()
{
    gainSlider.setBounds(getWidth() / 5 * 4, 0, getWidth() / 5, getHeight());
    
    onOffButton.setBounds(0, getHeight() / 5 * 4, getWidth() / 5, getHeight() / 5);
}

void ChannelMeter::buttonClicked(juce::Button* button)
{
    DBG(int(button->getToggleState()));
}
