/*
 Author: Brandon Ferrante
 Email: bmf124@maimi.edu
 MMI 603 DSP 2 Final Project
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BrandonFerrante_603FinalAudioProcessor::BrandonFerrante_603FinalAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    // Initialize Audio Parameter variables
    thresholdParameter = new juce::AudioParameterFloat(juce::ParameterID("1", 1), "Threshold Knob", -50.0f, 0.0f, -20.0f);
    ratioParameter = new juce::AudioParameterFloat(juce::ParameterID("2", 2), "Ratio Knob", 1.0f, 30.0f, 2.0f);
    kneeParameter = new juce::AudioParameterFloat(juce::ParameterID("3", 3), "Knee Knob", 1.0f, 10.0f, 0.7f);
    attackParameter = new juce::AudioParameterFloat(juce::ParameterID("4", 4), "Attack Knob", 0.0f, 200.0f, 15.0f);
    releaseParameter = new juce::AudioParameterFloat(juce::ParameterID("5", 5), "Release Knob", 5.0f, 5000.0f, 50.0f);
    dryWetParameter = new juce::AudioParameterFloat(juce::ParameterID("6", 6), "Dry/Wet Knob", 0.0f, 100.0f, 100.0f);
    makeupGainParameter = new juce::AudioParameterFloat(juce::ParameterID("7", 7), "Makeup Gain Knob", -30.0f, 30.0f, 0.0f);
    inputGainParameter = new juce::AudioParameterFloat(juce::ParameterID("8", 8), "Input Gain Knob", -30.0f, 30.0f, 0.0f);
    outputGainParameter = new juce::AudioParameterFloat(juce::ParameterID("9", 9), "Output Gain Knob", -30.0f, 30.0f, 0.0f);
    typeSwitchParameter = new juce::AudioParameterBool(juce::ParameterID("10", 10), "Dynamics Type Toggle", true);
    
    //Add Audio Parameters to the Parameter Tree with addParameter()
    addParameter(thresholdParameter);
    addParameter(ratioParameter);
    addParameter(kneeParameter);
    addParameter(attackParameter);
    addParameter(releaseParameter);
    addParameter(dryWetParameter);
    addParameter(makeupGainParameter);
    addParameter(inputGainParameter);
    addParameter(outputGainParameter);
    addParameter(typeSwitchParameter);
    
    // Get actual values to use for calculations and updating
    thresholdValue = *thresholdParameter;
    ratioValue = *ratioParameter;
    kneeValue = *kneeParameter;
    attackValue= *attackParameter;
    releaseValue = *releaseParameter;
    dryWetValue = *dryWetParameter;
    makeupGainValue = *makeupGainParameter;
    inputGainValue = *inputGainParameter;
    outputGainValue = *outputGainParameter;
    dynamicsType = *typeSwitchParameter;    
}

BrandonFerrante_603FinalAudioProcessor::~BrandonFerrante_603FinalAudioProcessor()
{
}

//==============================================================================
const juce::String BrandonFerrante_603FinalAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BrandonFerrante_603FinalAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BrandonFerrante_603FinalAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BrandonFerrante_603FinalAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BrandonFerrante_603FinalAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BrandonFerrante_603FinalAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BrandonFerrante_603FinalAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BrandonFerrante_603FinalAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BrandonFerrante_603FinalAudioProcessor::getProgramName (int index)
{
    return {};
}

void BrandonFerrante_603FinalAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BrandonFerrante_603FinalAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    fs = sampleRate;
    delayValue.resize(getTotalNumInputChannels(), 0.0f);
}

void BrandonFerrante_603FinalAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BrandonFerrante_603FinalAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void BrandonFerrante_603FinalAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
    
    int numChannels = buffer.getNumChannels();
    int numSamples = buffer.getNumSamples();
    
    // Check to see if values differ from parameters. If so, update.
    if (parametersChanged())
    {
        updateParameters();
    }
    
    // Convert dry/wet from percentage to 0-1 scale
    float c0 = dryWetValue * 0.01f; // wet
    float d0 = 1 - (dryWetValue * 0.01f); // dry
    
    // Apply input gain
    applyInputGain(buffer, inputGainValue);
    
    // Calculate envelope using envelopeDetector()
    juce::AudioBuffer<float> envelope_db = envelopeDetector(buffer);
    
    float y_db; // output of dynamics processor
    
    // Process
    for (int channel = 0; channel < numChannels; channel++)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        for (int n = 0; n < numSamples; n++)
        {
            float d = envelope_db.getSample(channel, n); // detector output current sample
            
            // Compressor
            if (dynamicsType == true)
            {
                if (2 * (d - thresholdValue) < -kneeValue)
                {
                    y_db = d;
                }
                else if (2 * abs(d - thresholdValue) <= kneeValue)
                {
                    y_db = d + (((1 / (ratioValue - 1)) * std::pow(d - thresholdValue + (kneeValue / 2), 2)) / 2 * kneeValue);
                }
                else if (2 * (d - thresholdValue) > kneeValue)
                {
                    y_db = thresholdValue + ((d - thresholdValue) / ratioValue);
                }
            }
            
            // Expander
            else if (dynamicsType == false)
            {
                if (2 * (d - thresholdValue) > kneeValue)
                {
                    y_db = d;
                }
                else if (2 * abs(d - thresholdValue) > -kneeValue)
                {
                    y_db = d - (((1 / ratioValue) * std::pow(d - thresholdValue - (kneeValue / 2), 2)) / 2 * kneeValue);
                }
                else if (2 * (d - thresholdValue) <= -kneeValue)
                {
                    y_db = thresholdValue + ratioValue * (d - thresholdValue);
                }
            }
            
            // Gain reduction / expansion calculation
            float g_db = y_db - d; // final gain in db
            float G_mag = dbToMag(g_db); // final gain in magnitude
            
            // Makeup and reduction / expansion gain application
            float makeupGain_mag = dbToMag(makeupGainValue);
            float z = channelData[n] * G_mag * makeupGain_mag;
            
            // Apply dry/wet mix
            channelData[n] = z * c0 + channelData[n] * d0;
        }
    }

    // Apply output gain
    applyOutputGain(buffer, outputGainValue);
}

//==============================================================================
bool BrandonFerrante_603FinalAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BrandonFerrante_603FinalAudioProcessor::createEditor()
{
    return new BrandonFerrante_603FinalAudioProcessorEditor (*this);
}

//==============================================================================
void BrandonFerrante_603FinalAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BrandonFerrante_603FinalAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BrandonFerrante_603FinalAudioProcessor();
}

// db to mag converter
float BrandonFerrante_603FinalAudioProcessor::dbToMag(float db_val)
{
    return std::pow(10.0f, db_val / 20.0f);
}

// mag to db converter
float BrandonFerrante_603FinalAudioProcessor::magToDB(float mag_val)
{
    return 20.0f * std::log10(mag_val);
}

// Apply the input gain to the entire buffer
void BrandonFerrante_603FinalAudioProcessor::applyInputGain(juce::AudioBuffer<float>& buffer, float inputGain_db)
{
    int numChannels = buffer.getNumChannels();
    int numSamples = buffer.getNumSamples();
    
    float inputGain_mag = dbToMag(inputGain_db);
    
    for (int channel = 0; channel < numChannels; channel++)
    {
        float *channelData = buffer.getWritePointer(channel);
        
        for (int n = 0; n < numSamples; n++)
        {
            channelData[n] = channelData[n] * inputGain_mag;
        }
    }
}

// Apply the output gain to the entire buffer
void BrandonFerrante_603FinalAudioProcessor::applyOutputGain(juce::AudioBuffer<float>& buffer, float outputGain_db)
{
    int numChannels = buffer.getNumChannels();
    int numSamples = buffer.getNumSamples();
    
    float outputGain_mag = dbToMag(outputGain_db);
    
    for (int channel = 0; channel < numChannels; channel++)
    {
        float *channelData = buffer.getWritePointer(channel);
        
        for (int n = 0; n < numSamples; n++)
        {
            channelData[n] = channelData[n] * outputGain_mag;
        }
    }
}

// Envelope Detector
juce::AudioBuffer<float> BrandonFerrante_603FinalAudioProcessor::envelopeDetector(const juce::AudioBuffer<float>& buffer)
{
    int numChannels = buffer.getNumChannels();
    int numSamples = buffer.getNumSamples();
    
    float attack_seconds = attackValue / 1000.0f; // attackValue is in ms
    float release_seconds = releaseValue / 1000.0f; // releaseValue is in ms
    float a0 = 1 - std::exp(-1 / (fs * attack_seconds));
    float b1 = std::exp(-1 / (fs * release_seconds));
    
    juce::AudioBuffer<float> envelope_db(numChannels, numSamples);
    
    for (int channel = 0; channel < numChannels; channel++)
    {
        for (int n = 0; n < numSamples; n++)
        {
            float abs_val = std::abs(buffer.getSample(channel, n));
            float forward_val = 	
            delayValue[channel] = forward_val;
            
            float value = forward_val > 0 ? magToDB(forward_val) : -96;
            envelope_db.setSample(channel, n, value);
        }
    }
    return envelope_db;
}

void BrandonFerrante_603FinalAudioProcessor::updateParameters()
{
    thresholdValue = *thresholdParameter;
    ratioValue = *ratioParameter;
    kneeValue = *kneeParameter;
    attackValue= *attackParameter;
    releaseValue = *releaseParameter;
    dryWetValue = *dryWetParameter;
    makeupGainValue = *makeupGainParameter;
    inputGainValue = *inputGainParameter;
    outputGainValue = *outputGainParameter;
    dynamicsType = *typeSwitchParameter;
}

bool BrandonFerrante_603FinalAudioProcessor::parametersChanged()
{
    return  thresholdValue != *thresholdParameter ||
            ratioValue != *ratioParameter ||
            kneeValue != *kneeParameter ||
            attackValue != *attackParameter ||
            releaseValue != *releaseParameter ||
            dryWetValue != *dryWetParameter ||
            makeupGainValue != *makeupGainParameter ||
            inputGainValue != *inputGainParameter ||
            outputGainValue != *outputGainParameter ||
            dynamicsType != *typeSwitchParameter;
}

