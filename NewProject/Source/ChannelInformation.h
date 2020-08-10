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
    ChannelInformation(int channelNum);
    
    ~ChannelInformation();
    
    void setOnState(bool newState);
    bool getOnState() const;
    
    void setChannelName(const juce::String& newName);
    juce::String getChannelName() const;
    
    void setMappedIndex(int newIndex);
    int getMappedIndex() const;
    
    void setCurrentPeak(float newPeak);
    float getCurrentPeak() const;
    
    float getActualPeak() const;
    
    class Listener
    {
    public:
        virtual ~Listener(){};
        
        virtual void currentPeakChanged(ChannelInformation* informationChanged) = 0;
    };
    
    void addListener(Listener* listener);
    void removeListener(Listener* listener);
    
private:
    void timerCallback() override;
    
    bool onState;
    juce::String channelName;
    int mappedIndex;
    
    //Current peak is a level which drops for the meter and actual peak is a level that does not drop for the label
    float currentPeakLevel;
    float actualPeak;
    
    std::vector<Listener*> listeners;
};
