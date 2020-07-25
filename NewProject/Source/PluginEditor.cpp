/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::black);
    if(!audioProcessor.getIfAudioOnChannel(0))
    {
        //Left rectangle
        g.drawRect(50, 50, 100, 100);
    }
    else
    {
        g.fillRect(50, 50, 100, 100);
    }
    
    if(!audioProcessor.getIfAudioOnChannel(1))
    {
        //Right rectangle
        g.drawRect(getWidth()-150, 50, 100, 100);
    }
    else
    {
        g.fillRect(getWidth()-150, 50, 100, 100);
    }
}

void NewProjectAudioProcessorEditor::resized()
{
    
}
