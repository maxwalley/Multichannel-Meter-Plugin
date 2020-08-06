/*
  ==============================================================================

    ChannelInformation.h
    Created: 4 Aug 2020 10:26:28am
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ChannelInformation  : public juce::Timer
{
public:
    ChannelInformation();
    ChannelInformation(const juce::String& channelName);
    
    ~ChannelInformation();
    
    void setOnState(bool newState);
    bool getOnState() const;
    
    void setChannelName(const juce::String& newName);
    juce::String getChannelName() const;
    
    void setMappedIndex(int newIndex);
    int getMappedIndex() const;
    
    void setCurrentPeak(float newPeak);
    float getCurrentPeak() const;
    
    class Listener
    {
    public:
        virtual ~Listener(){};
        
        virtual void currentPeakChanged(ChannelInformation* informationChanged) = 0;
    };
    
private:
    void timerCallback() override;
    
    bool onState;
    juce::String channelName;
    int mappedIndex;
    float currentPeakLevel;
    
    std::vector<Listener*> listeners;
};
