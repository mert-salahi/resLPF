/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ResLpfAudioProcessor::ResLpfAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
    resLPF_L(),
    resLPF_R()
#endif
{
    // Set initial filter configuration
    level = 0.5;
    fcutoff = 5000;
    resonance = 0.1;
    
    double fcutoffNorm = fcutoff * (2.0 / 44100.0);
    resLPF_L.updateCoeffecients(fcutoffNorm, resonance);
    resLPF_R.updateCoeffecients(fcutoffNorm, resonance);
}

ResLpfAudioProcessor::~ResLpfAudioProcessor()
{
}

//==============================================================================
const String ResLpfAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ResLpfAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ResLpfAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ResLpfAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ResLpfAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ResLpfAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ResLpfAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ResLpfAudioProcessor::setCurrentProgram (int index)
{
}

const String ResLpfAudioProcessor::getProgramName (int index)
{
    return {};
}

void ResLpfAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ResLpfAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
//    double fcutoffNorm = fcutoff * (2.0 / getSampleRate());
//    resLPF_L.updateCoeffecients(fcutoffNorm, resonance);
//    resLPF_R.updateCoeffecients(fcutoffNorm, resonance);
}

void ResLpfAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ResLpfAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ResLpfAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is where the signal processing happens
    // Update filter coeffecients for given cutoff frequency and resonance, then filter
    double fcutoffNorm = fcutoff * (2.0 / getSampleRate());
    resLPF_L.updateCoeffecients(fcutoffNorm, resonance);
    resLPF_R.updateCoeffecients(fcutoffNorm, resonance);
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        for(int sample = 0; sample < buffer.getNumSamples(); sample++)
        {

            if(channel == 0)
            {
                channelData[sample] = (level) * resLPF_L.updateSample(buffer.getSample(channel, sample)) + (1.0 - level) * buffer.getSample(channel, sample);
            }
            else
            {
                channelData[sample] = (level) * resLPF_R.updateSample(buffer.getSample(channel, sample)) + (1.0 - level) * buffer.getSample(channel, sample);
            }
        }
    }
}

//==============================================================================
bool ResLpfAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ResLpfAudioProcessor::createEditor()
{
    return new ResLpfAudioProcessorEditor (*this);
}

//==============================================================================
void ResLpfAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ResLpfAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ResLpfAudioProcessor();
}
