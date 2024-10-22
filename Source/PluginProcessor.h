/*
 Author: Brandon Ferrante
 Email: bmf124@maimi.edu
 MMI 603 DSP 2 Final Project
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class BrandonFerrante_603FinalAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    BrandonFerrante_603FinalAudioProcessor();
    ~BrandonFerrante_603FinalAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    juce::AudioBuffer<float> rmsEnvelope(const juce::AudioBuffer<float>& buffer, int windowSize);
    float dbToMag(float db_val);
    float magToDB(float mag_val);
    void applyInputGain(juce::AudioBuffer<float>& buffer, float inputGain_db);
    void applyOutputGain(juce::AudioBuffer<float>& buffer, float outputGain_db);
    juce::AudioBuffer<float> envelopeDetector(const juce::AudioBuffer<float>& buffer);
    void updateParameters();
    bool parametersChanged();

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrandonFerrante_603FinalAudioProcessor)
    
    juce::AudioParameterFloat *thresholdParameter;
    juce::AudioParameterFloat *ratioParameter;
    juce::AudioParameterFloat *kneeParameter;
    juce::AudioParameterFloat *attackParameter;
    juce::AudioParameterFloat *releaseParameter;
    juce::AudioParameterFloat *dryWetParameter;
    juce::AudioParameterFloat *makeupGainParameter;
    juce::AudioParameterFloat *inputGainParameter;
    juce::AudioParameterFloat *outputGainParameter;
    juce::AudioParameterBool *typeSwitchParameter;
    
    float thresholdValue;
    float ratioValue;
    float kneeValue;
    float attackValue;
    float releaseValue;
    float dryWetValue;
    float makeupGainValue;
    float inputGainValue;
    float outputGainValue;
    bool dynamicsType;
    
    // delayValue vector for envelopeDetector
    // enables delayValue information to persist between processBlock() calls
    std::vector<float> delayValue;
    
    double fs = 44100;
};
