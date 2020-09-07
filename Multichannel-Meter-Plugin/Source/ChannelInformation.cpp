/*
  ==============================================================================

    ChannelInformation.cpp
    Created: 4 Aug 2020 10:26:28am
    Author:  Max Walley

  ==============================================================================
*/

#include "ChannelInformation.h"

ChannelInformation::ChannelInformation(int channelNum)  : onState(true), channelName("Channel " + juce::String(channelNum)), mappedIndex(-1), currentPeakLevel(0.0), actualPeak(0.0), gain(0.0)
{
    juce::Timer::startTimer(10);
}

ChannelInformation::~ChannelInformation()
{
    
}

void ChannelInformation::setOnState(bool newState)
{
    onState = newState;
}

bool ChannelInformation::getOnState() const
{
    return onState;
}

juce::String ChannelInformation::getChannelName() const
{
    return channelName;
}

void ChannelInformation::setMappedIndex(int newIndex)
{
    mappedIndex = newIndex;
}

int ChannelInformation::getMappedIndex() const
{
    return mappedIndex;
}

void ChannelInformation::setCurrentPeak(float newPeak)
{
    if(newPeak != currentPeakLevel)
    {
        currentPeakLevel = newPeak;
        actualPeak = newPeak;
    }
    
    if (newPeak == 0.0)
    {
        actualPeak = 0.0;
    }
}

float ChannelInformation::getCurrentPeak() const
{
    return currentPeakLevel;
}

float ChannelInformation::getActualPeak() const
{
    return actualPeak;
}

void ChannelInformation::setGain(float newGain)
{
    gain = newGain;
}

float ChannelInformation::getGain() const
{
    return gain;
}

void ChannelInformation::addListener(ChannelInformation::Listener* listener)
{
    listeners.push_back(listener);
}

void ChannelInformation::removeListener(ChannelInformation::Listener* listener)
{
    auto iteratorToDel = std::find(listeners.begin(), listeners.end(), listener);
    
    if(iteratorToDel != listeners.end())
    {
        listeners.erase(iteratorToDel);
    }
}

void ChannelInformation::timerCallback()
{
    if(currentPeakLevel > 0)
    {
        if(currentPeakLevel > 0.01)
        {
            currentPeakLevel -= 0.01;
        }
        else
        {
            currentPeakLevel = 0.0;
            actualPeak = 0.0;
        }
        std::for_each(listeners.begin(), listeners.end(), [this](Listener* currentLis)
        {
            currentLis->currentPeakChanged(this);
        });
    }
}
