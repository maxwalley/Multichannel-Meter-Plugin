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

}

OnOffButton::~OnOffButton()
{
    
}

void OnOffButton::paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    if(shouldDrawButtonAsDown)
    {
        g.setColour(juce::Colours::silver);
    }
    else
    {
        g.setColour(juce::Colours::black);
    }
    
    juce::Path newPath;
    
    newPath.addArc(getWidth() / 6, getHeight() / 6, getWidth() / 6 * 4, getHeight() / 6 * 4, juce::float_Pi * 0.25, juce::float_Pi * 1.75, true);
    
    g.strokePath(newPath, juce::PathStrokeType(1.5));
    
    g.drawLine(getWidth() / 2 - 1, getHeight() / 8 , getWidth() / 2 - 1, getHeight() / 2, 1.5);
}

//==============================================================================
ChannelMeter::ChannelMeter() : displayedInformation(temp)
{
    
    addAndMakeVisible(gainSlider);
    addAndMakeVisible(onOffButton);
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
    
    g.drawLine(0, getHeight() / 5 * 4, getWidth() / 5 * 4, getHeight() / 5 * 4);
    
    g.drawLine(getWidth() / 5, getHeight() / 5 * 4, getWidth() / 5, getHeight());
}

void ChannelMeter::resized()
{
    gainSlider.setBounds(getWidth() / 5 * 4, 0, getWidth(), getHeight());
    
    onOffButton.setBounds(0, getHeight() / 5 * 4, getWidth() / 5, getHeight() / 5);
}
