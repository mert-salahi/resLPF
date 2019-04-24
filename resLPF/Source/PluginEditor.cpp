/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ResLpfAudioProcessorEditor::ResLpfAudioProcessorEditor (ResLpfAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 100);
    
    addAndMakeVisible (levelSlider);
    levelSlider.setRange (0.0, 1.0);
    levelSlider.setTextValueSuffix (" ");
    levelSlider.addListener (this);
    addAndMakeVisible (levelLabel);
    levelLabel.setText ("Level", dontSendNotification);
    levelLabel.attachToComponent (&levelSlider, true);
    
    addAndMakeVisible (fcutoffSlider);
    fcutoffSlider.setRange (20, 22000);
    fcutoffSlider.setTextValueSuffix (" ");
    fcutoffSlider.addListener (this);
    addAndMakeVisible (fcutoffLabel);
    fcutoffLabel.setText ("Cutoff Frequency", dontSendNotification);
    fcutoffLabel.attachToComponent (&fcutoffSlider, true);
    
    addAndMakeVisible (resonanceSlider);
    resonanceSlider.setRange (0.0, 10.0);
    resonanceSlider.setTextValueSuffix (" ");
    resonanceSlider.addListener (this);
    addAndMakeVisible (resonanceLabel);
    resonanceLabel.setText ("Resonance", dontSendNotification);
    resonanceLabel.attachToComponent (&resonanceSlider, true);
    
    levelSlider.setValue(0.5);
    fcutoffSlider.setValue(5000.0);
    resonanceSlider.setValue(0.5);
}

ResLpfAudioProcessorEditor::~ResLpfAudioProcessorEditor()
{
}

//==============================================================================
void ResLpfAudioProcessorEditor::paint (Graphics& g)
{
    // fill the whole window white
    g.fillAll (Colours::palevioletred);
    // set the current drawing colour to black
    g.setColour (Colours::black);
    // set the font size and draw text to the screen
    g.setFont (15.0f);
    g.drawFittedText ("Mert's Resonant LPF", 0, 0, getWidth(), 30, Justification::centred, 1);
}

void ResLpfAudioProcessorEditor::resized()
{
    auto sliderLeft = 120;
    levelSlider.setBounds (sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
    fcutoffSlider.setBounds (sliderLeft, 50, getWidth() - sliderLeft - 10, 20);
    resonanceSlider.setBounds (sliderLeft, 80, getWidth() - sliderLeft - 10, 20);
}

void ResLpfAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &levelSlider)
    {
        processor.level =  levelSlider.getValue();
    }
    else if (slider == &fcutoffSlider)
    {
        processor.fcutoff = fcutoffSlider.getValue();
    }
    else if (slider == &resonanceSlider)
    {
        processor.resonance = resonanceSlider.getValue();
    }
}
