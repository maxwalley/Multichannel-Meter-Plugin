/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ChannelMeter.h"

//==============================================================================
/**
*/
class InputGainSlider   :   public juce::Slider
{
public:
    InputGainSlider();
    ~InputGainSlider();
    
private:
    double getValueFromText(const juce::String& text) override;
    
    juce::String getTextFromValue(double value) override;
};

/**
*/
class NewProjectAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                        public juce::ChangeListener
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& audioProcessor;
    
    InputGainSlider inputGainSlider;
    
    juce::AudioProcessorValueTreeState::SliderAttachment gainSliderAttachment;
    
    std::vector<std::unique_ptr<ChannelMeter>> meters;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};
