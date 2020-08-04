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
    : AudioProcessorEditor (&p), audioProcessor (p), gainSliderAttachment(audioProcessor.getVTS(), "gain", inputGainSlider)
{
    
    audioProcessor.addChangeListener(this);
    
    addAndMakeVisible(inputGainSlider);
    inputGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    inputGainSlider.setValue(0.5);
    inputGainSlider.setRange(0, 1);
    inputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, inputGainSlider.getWidth(), 20);
    inputGainSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    
    
    meters.push_back(std::make_unique<ChannelMeter>());
    
    std::for_each(meters.begin(), meters.end(), [this](const std::unique_ptr<ChannelMeter>& ptr)
    {
        addAndMakeVisible(*ptr);
    });
    
    //addAndMakeVisible(*meters[0]);
    
    setSize (400, 300);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    /*g.setColour(juce::Colours::black);
    
    //Draws the outline for the left channel
    g.drawRect(50, 50, 100, 100);
    
    float leftLevel = audioProcessor.getPeakLevelOnChannel(0);
    
    leftLevel *= 100;
    
    g.fillRect(50.0, 50.0 + (100 - leftLevel), 100.0, leftLevel);
    
    
    g.drawRect(getWidth()-150, 50, 100, 100);
    
    float rightLevel = audioProcessor.getPeakLevelOnChannel(1);
    
    rightLevel *= 100;
    
    g.fillRect(getWidth()-150.0, 50.0 + (100 - rightLevel), 100.0, rightLevel);*/
    
    
}

void NewProjectAudioProcessorEditor::resized()
{
    inputGainSlider.setBounds(150, 50, 100, 200);
    
    meters[0]->setBounds(50, 50, 100, 100);
}

void NewProjectAudioProcessorEditor::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    repaint(50, 50, 100, 100);
    repaint(getWidth()-150, 50, 100, 100);
}
