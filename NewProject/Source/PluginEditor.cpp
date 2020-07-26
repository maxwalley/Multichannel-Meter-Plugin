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
    
    audioProcessor.addChangeListener(this);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::black);
    
    //Draws the outline for the left channel
    g.drawRect(50, 50, 100, 100);
    
    float leftLevel = audioProcessor.getAudioLevelOnChannel(0);
    
    if(leftLevel < 0)
    {
        leftLevel *= -1;
    }
    
    leftLevel *= 100;
    
    g.fillRect(50.0, 50.0 + (100 - leftLevel), 100.0, leftLevel);
    
    
    g.drawRect(getWidth()-150, 50, 100, 100);
    
    float rightLevel = audioProcessor.getAudioLevelOnChannel(1);
    
    if(rightLevel < 0)
    {
        rightLevel *= -1;
    }
    
    rightLevel *= 100;
    
    g.fillRect(getWidth()-150.0, 50.0 + (100 - rightLevel), 100.0, rightLevel);
}

void NewProjectAudioProcessorEditor::resized()
{
    
}

void NewProjectAudioProcessorEditor::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    repaint(50, 50, 100, 100);
    repaint(getWidth()-150, 50, 100, 100);
}
