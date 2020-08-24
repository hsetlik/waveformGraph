//
//  PlayheadComponent.cpp
//  waveformGraph - App
//
//  Created by Hayden Setlik on 8/24/20.
//

#include "PlayheadComponent.hpp"

void PlayheadComponent::paint(juce::Graphics& g)
{
    auto duration = (float) transportSource.getLengthInSeconds();
    
            if (duration > 0.0)
            {
                auto audioPosition = (float) transportSource.getCurrentPosition();
                auto drawPosition = (audioPosition / duration) * (float) getWidth();
    
                g.setColour (juce::Colours::green);
                g.drawLine (drawPosition, 0.0f, drawPosition, (float) getHeight(), 2.0f);
}
}
