/*
 Author: Brandon Ferrante
 Email: bmf124@maimi.edu
 MMI 603 DSP 2 Final Project
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class BrandonFerrante_603FinalAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    BrandonFerrante_603FinalAudioProcessorEditor (BrandonFerrante_603FinalAudioProcessor&);
    ~BrandonFerrante_603FinalAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BrandonFerrante_603FinalAudioProcessor& audioProcessor;
    
    juce::Slider thresholdKnob;
    juce::Slider ratioKnob;
    juce::Slider kneeKnob;
    juce::Slider attackKnob;
    juce::Slider releaseKnob;
    juce::Slider dryWetKnob;
    juce::Slider makeupGainKnob;
    juce::Slider inputGainKnob;
    juce::Slider outputGainKnob;
    juce::ToggleButton typeSwitch;
    
    juce::Label thresholdKnobLabel;
    juce::Label ratioKnobLabel;
    juce::Label kneeKnobLabel;
    juce::Label attackKnobLabel;
    juce::Label releaseKnobLabel;
    juce::Label dryWetKnobLabel;
    juce::Label makeupGainKnobLabel;
    juce::Label inputGainKnobLabel;
    juce::Label outputGainKnobLabel;
    juce::Label typeSwitchLabel;
    
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
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrandonFerrante_603FinalAudioProcessorEditor)
};
