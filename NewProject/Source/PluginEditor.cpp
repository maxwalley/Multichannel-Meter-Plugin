/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

InputGainSlider::InputGainSlider()
{
    setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, juce::Colours::white);
    
    setColour(juce::Slider::ColourIds::textBoxHighlightColourId, juce::Colours::black);
    
    setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    
    getLookAndFeel().setColour(juce::Label::ColourIds::textWhenEditingColourId, juce::Colours::black);
}

InputGainSlider::~InputGainSlider()
{
    
}

double InputGainSlider::getValueFromText(const juce::String& text)
{
    if(text.getIntValue() >= 0)
    {
        return 1.0;
    }
    return juce::Decibels::decibelsToGain(float(text.getIntValue()));
}

juce::String InputGainSlider::getTextFromValue(double value)
{
    //this is needed to get rid of the + in +0.00 dB
    if(value == 1.0)
    {
        return "0.00 dB";
    }
    
    return juce::Decibels::toString(juce::Decibels::gainToDecibels(value));
}

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    audioProcessor.addChangeListener(this);
    
    setSize (400, 300);
    
    refreshSliders();
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    
}

void NewProjectAudioProcessorEditor::resized()
{
    if(meters.size() >= 1)
    {
        meters[0]->setBounds(50, 50, 100, 100);
    }
}

void NewProjectAudioProcessorEditor::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    refreshSliders();
}

void NewProjectAudioProcessorEditor::refreshSliders()
{
    if(meters.size() != audioProcessor.getTotalNumInputChannels())
    {
    
        //If meters need to be added
        for(size_t i = meters.size(); i < audioProcessor.getTotalNumInputChannels(); i++)
        {
            meters.push_back(std::make_unique<ChannelMeter>(*(audioProcessor.getInfoForChannel(i))));
        
            addAndMakeVisible(meters[i].get());
        }
    
        //If meters need to be removed
        for(size_t i = meters.size() - 1; i > audioProcessor.getTotalNumInputChannels(); i--)
        {
            meters.erase(meters.begin() + i);
        }
    }
    resized();
}
