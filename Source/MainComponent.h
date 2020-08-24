#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
 //more example changes
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent,
                       private juce::ChangeListener
{
public:
    //==============================================================================
    MainComponent() : state(stopped)
    {
        addAndMakeVisible (&openButton);
        openButton.setButtonText ("Open...");
        openButton.onClick = [this] { openButtonClicked(); };

        addAndMakeVisible (&playButton);
        playButton.setButtonText ("Play");
        playButton.onClick = [this] { playButtonClicked(); };
        playButton.setColour (juce::TextButton::buttonColourId, juce::Colours::green);
        playButton.setEnabled (false);

        addAndMakeVisible (&stopButton);
        stopButton.setButtonText ("Stop");
        stopButton.onClick = [this] { stopButtonClicked(); };
        stopButton.setColour (juce::TextButton::buttonColourId, juce::Colours::red);
        stopButton.setEnabled (false);
        
        formatManager.registerBasicFormats();
        
        setSize (800, 600);
        transportSource.addChangeListener(this);
        setAudioChannels (0, 2);
        
    }

    ~MainComponent() override
    {
        // This shuts down the audio device and clears the audio source.
        shutdownAudio();
    }

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
        transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    }

    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override
    {
        if(readerSource.get() == nullptr)
            bufferToFill.clearActiveBufferRegion();
        else
            transportSource.getNextAudioBlock(bufferToFill);
    }

    void releaseResources() override
    {
        // This will be called when the audio device stops, or when it is being
        // restarted due to a setting change.
        transportSource.releaseResources();
        // For more details, see the help for AudioProcessor::releaseResources()
    }

    //==============================================================================
    void paint (juce::Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

        // You can add your drawing code here!
    }

    void resized() override
    {
        openButton.setBounds (10, 10, getWidth() - 20, 20);
        playButton.setBounds (10, 40, getWidth() - 20, 20);
        stopButton.setBounds (10, 70, getWidth() - 20, 20);
    }
    void changeListenerCallback(juce::ChangeBroadcaster* source) override
    {
        if (source == &transportSource) transportSourceChanged();
    }


private:
    enum transportState{
        stopped,
        starting,
        playing,
        stopping
    };
    void changeState(transportState newState){
        if(state != newState)
        {
            state = newState;
            switch(state)
            {
                case stopped :
                    stopButton.setEnabled(false);
                    playButton.setEnabled(true);
                    transportSource.setPosition(0.0);
                    break;
                case starting:
                    playButton.setEnabled(false);
                    transportSource.start();
                    break;
                case playing:
                    stopButton.setEnabled(true);
                    break;
                case stopping:
                    transportSource.stop();
                    break;
                default:
                    jassertfalse;
                    break;
            }
        }
        
    }
    void transportSourceChanged()
    {
        changeState (transportSource.isPlaying() ? playing : stopped);
    }
    void openButtonClicked()
    {
        juce::FileChooser chooser ("Select a Wave file to play...",
                                   {},
                                   "*.wav;*.mp3");

        if (chooser.browseForFileToOpen())
        {
            juce::File file (chooser.getResult());
            auto* reader = formatManager.createReaderFor (file);

            if (reader != nullptr)
            {
                std::unique_ptr<juce::AudioFormatReaderSource> newSource (new juce::AudioFormatReaderSource (reader, true));
                transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
                playButton.setEnabled (true);
                readerSource.reset (newSource.release());
            }
        }
    }
    void playButtonClicked()
    {
        changeState(starting);
    }
    void stopButtonClicked()
    {
        changeState(stopping);
    }
    juce::TextButton openButton;
    juce::TextButton playButton;
    juce::TextButton stopButton;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    transportState state;
    juce::AudioFormatManager formatManager;
    juce::AudioTransportSource transportSource;
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
