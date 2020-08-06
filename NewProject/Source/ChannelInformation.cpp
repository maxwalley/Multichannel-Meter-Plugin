/*
  ==============================================================================

    ChannelInformation.cpp
    Created: 4 Aug 2020 10:26:28am
    Author:  Max Walley

  ==============================================================================
*/

#include "ChannelInformation.h"

ChannelInformation::ChannelInformation()  : onState(true), channelName(""), mappedIndex(-1), currentPeakLevel(0.0)
{
    juce::Timer::startTimer(10);
}

ChannelInformation::ChannelInformation(int channelNum)  : onState(true), channelName("Channel " + juce::String(channelNum)), mappedIndex(-1), currentPeakLevel(0.0)
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

void ChannelInformation::setChannelName(const juce::String& newName)
{
    channelName = newName;
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
        std::for_each(listeners.begin(), listeners.end(), [this](Listener* currentLis){currentLis->currentPeakChanged(this);});
    }
}

float ChannelInformation::getCurrentPeak() const
{
    return currentPeakLevel;
}

void ChannelInformation::addListener(ChannelInformation::Listener* listener)
{
    listeners.push_back(listener);
}

void ChannelInformation::removeListener(ChannelInformation::Listener* listener)
{
    std::remove(listeners.begin(), listeners.end(), listener);
}

void ChannelInformation::timerCallback()
{
    if(currentPeakLevel > 0.01)
    {
        currentPeakLevel -= 0.01;
        std::for_each(listeners.begin(), listeners.end(), [this](Listener* currentLis){currentLis->currentPeakChanged(this);});
    }
}
