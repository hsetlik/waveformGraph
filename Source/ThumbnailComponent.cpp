//
//  ThumbnailComponent.cpp
//  waveformGraph - App
//
//  Created by Hayden Setlik on 8/24/20.
//

#include "ThumbnailComponent.hpp"


void ThumbnailComponent::setFile(const juce::File& file)
{
    thumbnail.setSource(new juce::FileInputSource (file));
}
void ThumbnailComponent::paint(juce::Graphics& g)
{
    if(thumbnail.getNumChannels() == 0)
    {
        paintIfNoFileLoaded(g);
    } else {
        paintIfFileLoaded(g);
    }
}
void ThumbnailComponent::paintIfNoFileLoaded(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::white);
    g.drawFittedText("No File Loaded", getLocalBounds(), juce::Justification::centred, 1);
    
}
void ThumbnailComponent::paintIfFileLoaded(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::lightblue);
    thumbnail.drawChannels (g, getLocalBounds(), 0.0, thumbnail.getTotalLength(), 1.0f);
}
void ThumbnailComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if(source == &thumbnail){
        thumbnailChanged();
    }
}
