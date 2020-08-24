//
//  PlayheadComponent.hpp
//  waveformGraph - App
//
//  Created by Hayden Setlik on 8/24/20.
//

#pragma once
#include <JuceHeader.h>

class PlayheadComponent : public juce::Component,
private juce::Timer
{
public:
    PlayheadComponent(const juce::AudioTransportSource& thisTransportSource)
    : transportSource(thisTransportSource)
    {
        startTimer(40);
    }
    
    void paint(juce::Graphics& g) override;
    
private:
    const juce::AudioTransportSource& transportSource;
    void timerCallback() override
    {
        repaint();
    }
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayheadComponent);
    
};
