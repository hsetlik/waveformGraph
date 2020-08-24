//
//  ThumbnailComponent.hpp
//  waveformGraph - App
//
//  Created by Hayden Setlik on 8/24/20.
//

#pragma once
#include <JuceHeader.h>
class ThumbnailComponent : public juce::Component,
                           private juce::ChangeListener
{
public:
    ThumbnailComponent(int sourceSamplesPerThumbnail,
                       juce::AudioFormatManager& formatManager,
                       juce::AudioThumbnailCache& thumbnailCache,
                       juce::AudioTransportSource& thisTransportSource)
    : thumbnail(sourceSamplesPerThumbnail, formatManager, thumbnailCache),
     transportSource(thisTransportSource)
    {
        thumbnail.addChangeListener(this);
    }
    void setFile(const juce::File& file);
    void paint(juce::Graphics& g) override;
    void paintIfNoFileLoaded(juce::Graphics& g);
    void paintIfFileLoaded(juce::Graphics& g);
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
private:
    juce::AudioThumbnail thumbnail;
    const juce::AudioTransportSource& transportSource;
    void thumbnailChanged()
    {
        repaint();
    }
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ThumbnailComponent);
};
