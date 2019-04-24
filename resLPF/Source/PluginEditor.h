/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ResLpfAudioProcessorEditor  : public AudioProcessorEditor,
                                    public Slider::Listener
{
public:
    ResLpfAudioProcessorEditor (ResLpfAudioProcessor&);
    ~ResLpfAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    void sliderValueChanged(Slider* slider) override;
    ResLpfAudioProcessor& processor;
    
    Slider levelSlider;
    Label levelLabel;
    Slider fcutoffSlider;
    Label fcutoffLabel;
    Slider resonanceSlider;
    Label resonanceLabel;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterLevelValue;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterCutoffValue;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterResValue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ResLpfAudioProcessorEditor)
};
