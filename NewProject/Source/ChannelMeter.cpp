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
    
    newLayout.sliderBounds = juce::Rectangle<int> (slider.getWidth() / 2, sliderHeightFifth + 10, slider.getWidth() / 2, (sliderHeightFifth * 4) - 18);
    
    newLayout.textBoxBounds = juce::Rectangle<int> (0, 0, slider.getWidth(), sliderHeightFifth);
    
    return newLayout;
}

juce::Label* GainSliderLookAndFeel::createSliderTextBox(juce::Slider& slider)
{
    std::unique_ptr<juce::Label> sliderLabel = std::make_unique<juce::Label>();
    
    sliderLabel->setColour(juce::Label::textColourId, juce::Colours::black);
    
    sliderLabel->setFont(juce::Font(10));
    sliderLabel->setJustificationType(juce::Justification::centred);
    
    return sliderLabel.release();
}

//==============================================================================

ChannelMeter::ChannelMeter(ChannelInformation& infoToDisplay)  : displayedInformation(infoToDisplay)
{
    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(juce::Slider::LinearVertical);
    gainSlider.setRange(0.0, 1.0, 0.01);
    gainSlider.setValue(0.5);
    gainSlider.setLookAndFeel(&gainSliderLAF);
    gainSlider.addListener(this);
    
    addAndMakeVisible(onOffButton);
    onOffButton.addListener(this);
    
    addAndMakeVisible(channelNameLabel);
    channelNameLabel.setText(displayedInformation.getChannelName(), juce::dontSendNotification);
    channelNameLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    channelNameLabel.setColour(juce::Label::backgroundColourId, juce::Colours::white);
    channelNameLabel.setJustificationType(juce::Justification::centred);
    channelNameLabel.setFont(juce::Font(10));
    
    addAndMakeVisible(peakLevelLabel);
    peakLevelLabel.setColour(juce::Label::backgroundColourId, juce::Colours::white);
    peakLevelLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    peakLevelLabel.setFont(juce::Font(10));
    
    displayedInformation.setCurrentPeak(0.6);
    displayedInformation.addListener(this);
}

ChannelMeter::~ChannelMeter()
{
    displayedInformation.removeListener(this);
}

void ChannelMeter::paint (juce::Graphics& g)
{
    int fifthHeight = getHeight() / 5;
    
    int meterStart = (fifthHeight * 3) - displayedInformation.getCurrentPeak() * (fifthHeight * 3) + fifthHeight;
    
    //Meter
    g.fillRect(0, meterStart, getWidth() / 5 * 4, fifthHeight * 4 - meterStart);
}

void ChannelMeter::paintOverChildren (juce::Graphics& g)
{
    g.setColour(juce::Colours::silver);
    
    int fifthHeight = getHeight() / 5;
    
    //Border
    g.drawRect(0, 0, getWidth(), getHeight(), 2.0);
    
    //Inner vertical line
    g.drawLine(fifthHeight * 4, fifthHeight, getWidth() / 5 * 4, getHeight());
    
    //Inner lower horizontal line
    g.drawLine(0, fifthHeight * 4, getWidth() / 5 * 4, fifthHeight * 4);
    
    //On/off button vertical line
    g.drawLine(getWidth() / 5, fifthHeight * 4, getWidth() / 5, getHeight());
    
    //Inner upper horizontal line
    g.drawLine(0, fifthHeight, getWidth(), getHeight() / 5);
    
    //Slider label vertical line
    g.drawLine(getWidth() / 5 * 3, 0, getWidth() / 5 * 3, fifthHeight);
}

void ChannelMeter::resized()
{
    gainSlider.setBounds(getWidth() / 5 * 3, 0, getWidth() / 5 * 2, getHeight());
    
    onOffButton.setBounds(0, getHeight() / 5 * 4, getWidth() / 5, getHeight() / 5);
    
    channelNameLabel.setBounds(0, 0, getWidth() / 5 * 3, getHeight() / 5);
    
    peakLevelLabel.setBounds(getWidth() / 5, getHeight() / 5 * 4, getWidth() / 5 * 3, getHeight() / 5);
}

void ChannelMeter::buttonClicked(juce::Button* button)
{
    displayedInformation.setOnState(button->getToggleState());
}

void ChannelMeter::currentPeakChanged(ChannelInformation* informationChanged)
{
    repaint(0, getHeight() / 5, getWidth() / 5 * 4, getHeight() / 5 * 3);
    peakLevelLabel.setText(juce::Decibels::toString( juce::Decibels::gainToDecibels(displayedInformation.getActualPeak())), juce::dontSendNotification);
}

void ChannelMeter::sliderValueChanged(juce::Slider* slider)
{
    displayedInformation.setGain(slider->getValue());
}
