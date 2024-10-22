/*
 Author: Brandon Ferrante
 Email: bmf124@maimi.edu
 MMI 603 DSP 2 Final Project
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BrandonFerrante_603FinalAudioProcessorEditor::BrandonFerrante_603FinalAudioProcessorEditor (BrandonFerrante_603FinalAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1200, 675);
    
    
    // addAndMakeVisible()
    addAndMakeVisible(thresholdKnob);
    addAndMakeVisible(ratioKnob);
    addAndMakeVisible(kneeKnob);
    addAndMakeVisible(attackKnob);
    addAndMakeVisible(releaseKnob);
    addAndMakeVisible(dryWetKnob);
    addAndMakeVisible(makeupGainKnob);
    addAndMakeVisible(inputGainKnob);
    addAndMakeVisible(outputGainKnob);
    addAndMakeVisible(typeSwitch);
    
    addAndMakeVisible(thresholdKnobLabel);
    addAndMakeVisible(ratioKnobLabel);
    addAndMakeVisible(kneeKnobLabel);
    addAndMakeVisible(attackKnobLabel);
    addAndMakeVisible(releaseKnobLabel);
    addAndMakeVisible(dryWetKnobLabel);
    addAndMakeVisible(makeupGainKnobLabel);
    addAndMakeVisible(inputGainKnobLabel);
    addAndMakeVisible(outputGainKnobLabel);
    addAndMakeVisible(typeSwitchLabel);
    

    // Stylize GUI components
    thresholdKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    thresholdKnob.setRange(-50, 0, 0.5f);
    thresholdKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 40);
    thresholdKnob.setTextValueSuffix(" dB");
    thresholdKnob.setSliderSnapsToMousePosition(true);
    thresholdKnob.setColour(juce::Slider::thumbColourId, juce::Colours::red);
    thresholdKnob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::white);
    thresholdKnob.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
    thresholdKnob.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    thresholdKnob.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::black);
    
    thresholdKnobLabel.setText("Threshold", juce::dontSendNotification);
    thresholdKnobLabel.setFont(juce::Font(24.0f));
    thresholdKnobLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    thresholdKnobLabel.setJustificationType(juce::Justification::centred);
    thresholdKnobLabel.attachToComponent(&thresholdKnob, false);
    
    
    ratioKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ratioKnob.setRange(1, 30, 0.1f);
    ratioKnob.setSkewFactor(0.5);
    ratioKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 40);
    ratioKnob.setTextValueSuffix(":1");
    ratioKnob.setSliderSnapsToMousePosition(true);
    ratioKnob.setColour(juce::Slider::thumbColourId, juce::Colours::orange);
    ratioKnob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::white);
    ratioKnob.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
    ratioKnob.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    ratioKnob.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::black);
    
    ratioKnobLabel.setText("Ratio", juce::dontSendNotification);
    ratioKnobLabel.setFont(juce::Font(24.0f));
    ratioKnobLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    ratioKnobLabel.setJustificationType(juce::Justification::centred);
    ratioKnobLabel.attachToComponent(&ratioKnob, false);
    
    
    kneeKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    kneeKnob.setRange(1, 10, 0.1f);
    kneeKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 40);
    kneeKnob.setSliderSnapsToMousePosition(true);
    kneeKnob.setColour(juce::Slider::thumbColourId, juce::Colours::yellow);
    kneeKnob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::white);
    kneeKnob.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
    kneeKnob.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    kneeKnob.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::black);
    
    kneeKnobLabel.setText("Knee", juce::dontSendNotification);
    kneeKnobLabel.setFont(juce::Font(24.0f));
    kneeKnobLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    kneeKnobLabel.setJustificationType(juce::Justification::centred);
    kneeKnobLabel.attachToComponent(&kneeKnob, false);
    
    
    attackKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    attackKnob.setRange(0, 200, 0.5f);
    attackKnob.setSkewFactor(0.5);
    attackKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 40);
    attackKnob.setTextValueSuffix(" ms");
    attackKnob.setSliderSnapsToMousePosition(true);
    attackKnob.setColour(juce::Slider::thumbColourId, juce::Colours::hotpink);
    attackKnob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::white);
    attackKnob.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
    attackKnob.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    attackKnob.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::black);
    
    attackKnobLabel.setText("Attack", juce::dontSendNotification);
    attackKnobLabel.setFont(juce::Font(24.0f));
    attackKnobLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    attackKnobLabel.setJustificationType(juce::Justification::centred);
    attackKnobLabel.attachToComponent(&attackKnob, false);
    
    
    releaseKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    releaseKnob.setRange(5, 5000, 0.5f);
    releaseKnob.setSkewFactor(0.4);
    releaseKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 40);
    releaseKnob.setTextValueSuffix(" ms");
    releaseKnob.setSliderSnapsToMousePosition(true);
    releaseKnob.setColour(juce::Slider::thumbColourId, juce::Colours::hotpink);
    releaseKnob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::white);
    releaseKnob.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
    releaseKnob.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    releaseKnob.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::black);
    
    releaseKnobLabel.setText("Release", juce::dontSendNotification);
    releaseKnobLabel.setFont(juce::Font(24.0f));
    releaseKnobLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    releaseKnobLabel.setJustificationType(juce::Justification::centred);
    releaseKnobLabel.attachToComponent(&releaseKnob, false);
    
    
    dryWetKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    dryWetKnob.setRange(0.0f, 100.0f, 0.5f);
    dryWetKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 40);
    dryWetKnob.setTextValueSuffix(" %");
    dryWetKnob.setSliderSnapsToMousePosition(true);
    dryWetKnob.setColour(juce::Slider::thumbColourId, juce::Colours::grey);
    dryWetKnob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::white);
    dryWetKnob.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
    dryWetKnob.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    dryWetKnob.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::black);
    
    dryWetKnobLabel.setText("Dry/Wet", juce::dontSendNotification);
    dryWetKnobLabel.setFont(juce::Font(24.0f));
    dryWetKnobLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    dryWetKnobLabel.setJustificationType(juce::Justification::centred);
    dryWetKnobLabel.attachToComponent(&dryWetKnob, false);
    
    
    makeupGainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    makeupGainKnob.setRange(-30, 30, 0.5f);
    makeupGainKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 40);
    makeupGainKnob.setTextValueSuffix(" dB");
    makeupGainKnob.setSliderSnapsToMousePosition(true);
    makeupGainKnob.setColour(juce::Slider::thumbColourId, juce::Colours::blueviolet);
    makeupGainKnob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::white);
    makeupGainKnob.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
    makeupGainKnob.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    makeupGainKnob.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::black);
    
    makeupGainKnobLabel.setText("Make Up", juce::dontSendNotification);
    makeupGainKnobLabel.setFont(juce::Font(24.0f));
    makeupGainKnobLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    makeupGainKnobLabel.setJustificationType(juce::Justification::centred);
    makeupGainKnobLabel.attachToComponent(&makeupGainKnob, false);
    
    
    inputGainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    inputGainKnob.setRange(-30, 30, 0.5f);
    inputGainKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 40);
    inputGainKnob.setTextValueSuffix(" dB");
    inputGainKnob.setSliderSnapsToMousePosition(true);
    inputGainKnob.setColour(juce::Slider::thumbColourId, juce::Colours::grey);
    inputGainKnob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::white);
    inputGainKnob.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
    inputGainKnob.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    inputGainKnob.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::black);
    
    inputGainKnobLabel.setText("Input", juce::dontSendNotification);
    inputGainKnobLabel.setFont(juce::Font(24.0f));
    inputGainKnobLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    inputGainKnobLabel.setJustificationType(juce::Justification::centred);
    inputGainKnobLabel.attachToComponent(&inputGainKnob, false);
    
    
    outputGainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    outputGainKnob.setRange(-30, 30, 0.5f);
    outputGainKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 40);
    outputGainKnob.setTextValueSuffix(" dB");
    outputGainKnob.setSliderSnapsToMousePosition(true);
    outputGainKnob.setColour(juce::Slider::thumbColourId, juce::Colours::grey);
    outputGainKnob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::white);
    outputGainKnob.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
    outputGainKnob.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    outputGainKnob.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::black);
    
    outputGainKnobLabel.setText("Output", juce::dontSendNotification);
    outputGainKnobLabel.setFont(juce::Font(24.0f));
    outputGainKnobLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    outputGainKnobLabel.setJustificationType(juce::Justification::centred);
    outputGainKnobLabel.attachToComponent(&outputGainKnob, false);
    
    
    typeSwitch.setColour(juce::ToggleButton::textColourId, juce::Colours::white);
    typeSwitch.setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::blue); // expander
    typeSwitch.setColour(juce::ToggleButton::tickColourId, juce::Colours::red); // compressor
    
    typeSwitchLabel.setText("Compressor / Expander", juce::dontSendNotification);
    typeSwitchLabel.setFont(juce::Font(24.0f));
    typeSwitchLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    typeSwitchLabel.setJustificationType(juce::Justification::bottomLeft);
    typeSwitchLabel.attachToComponent(&typeSwitch, false);
    
    
    // getParameters() to get Parameter tree
    auto parameterTree = audioProcessor.getParameters();
    
    
    // getUnchecked() to get pointer to specific GUI parameter and cast it as an Audio Parameter
    thresholdParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(0);
    ratioParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(1);
    kneeParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(2);
    attackParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(3);
    releaseParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(4);
    dryWetParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(5);
    makeupGainParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(6);
    inputGainParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(7);
    outputGainParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(8);
    typeSwitchParameter = (juce::AudioParameterBool*)parameterTree.getUnchecked(9);
    
    
    // set ranges
    thresholdKnob.setRange(thresholdParameter->range.start, thresholdParameter->range.end, thresholdParameter->range.interval);
    
    ratioKnob.setRange(ratioParameter->range.start, ratioParameter->range.end, ratioParameter->range.interval);
    
    kneeKnob.setRange(kneeParameter->range.start, kneeParameter->range.end, kneeParameter->range.interval);
    
    attackKnob.setRange(attackParameter->range.start, attackParameter->range.end, attackParameter->range.interval);
    
    releaseKnob.setRange(releaseParameter->range.start, releaseParameter->range.end, releaseParameter->range.interval);
    
    dryWetKnob.setRange(dryWetParameter->range.start, dryWetParameter->range.end, dryWetParameter->range.interval);
    
    makeupGainKnob.setRange(makeupGainParameter->range.start, makeupGainParameter->range.end,  makeupGainParameter->range.interval);
    
    inputGainKnob.setRange(inputGainParameter->range.start, inputGainParameter->range.end,  inputGainParameter->range.interval);
    
    outputGainKnob.setRange(outputGainParameter->range.start, outputGainParameter->range.end,  outputGainParameter->range.interval);
    
    
    // set default values
    thresholdKnob.setValue(*thresholdParameter, juce::NotificationType::dontSendNotification);
    ratioKnob.setValue(*ratioParameter, juce::NotificationType::dontSendNotification);
    kneeKnob.setValue(*kneeParameter, juce::NotificationType::dontSendNotification);
    attackKnob.setValue(*attackParameter, juce::NotificationType::dontSendNotification);
    releaseKnob.setValue(*releaseParameter, juce::NotificationType::dontSendNotification);
    dryWetKnob.setValue(*dryWetParameter, juce::NotificationType::dontSendNotification);
    makeupGainKnob.setValue(*makeupGainParameter, juce::NotificationType::dontSendNotification);
    inputGainKnob.setValue(*inputGainParameter, juce::NotificationType::dontSendNotification);
    outputGainKnob.setValue(*outputGainParameter, juce::NotificationType::dontSendNotification);
    typeSwitch.setToggleState(*typeSwitchParameter, juce::NotificationType::dontSendNotification);
    
    
    // callback function
    thresholdKnob.onValueChange = [this]
    {
        *thresholdParameter = thresholdKnob.getValue();
    };
    
    ratioKnob.onValueChange = [this]
    {
        *ratioParameter = ratioKnob.getValue();
    };
    
    kneeKnob.onValueChange = [this]
    {
        *kneeParameter = kneeKnob.getValue();
    };
    
    attackKnob.onValueChange = [this]
    {
        *attackParameter = attackKnob.getValue();
    };
    
    releaseKnob.onValueChange = [this]
    {
        *releaseParameter = releaseKnob.getValue();
    };
    
    dryWetKnob.onValueChange = [this]
    {
        *dryWetParameter = dryWetKnob.getValue();
    };
    
    makeupGainKnob.onValueChange = [this]
    {
        *makeupGainParameter = makeupGainKnob.getValue();
    };
    
    inputGainKnob.onValueChange = [this]
    {
        *inputGainParameter = inputGainKnob.getValue();
    };
    
    outputGainKnob.onValueChange = [this]
    {
        *outputGainParameter = outputGainKnob.getValue();
    };
    
    typeSwitch.onClick = [this]
    {
        *typeSwitchParameter = typeSwitch.getToggleState();
    };
}


BrandonFerrante_603FinalAudioProcessorEditor::~BrandonFerrante_603FinalAudioProcessorEditor()
{
}

//==============================================================================
void BrandonFerrante_603FinalAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::skyblue);
}

void BrandonFerrante_603FinalAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    auto x = getWidth() / 10;
    auto y = getHeight() / 10;
    
    // top row
    thresholdKnob.setBounds(1.5*x, 3.5*y, 3*x, 3*y);
    ratioKnob.setBounds(3.5*x, 3.5*y, 3*x, 3*y);
    makeupGainKnob.setBounds(5.5*x, 3.5*y, 3*x, 3*y);
    
    // bottom row
    kneeKnob.setBounds(2*x, 7.5*y, 2*x, 2*y);
    attackKnob.setBounds(4*x, 7.5*y, 2*x, 2*y);
    releaseKnob.setBounds(6*x, 7.5*y, 2*x, 2*y);
    
    // top sides
    typeSwitch.setBounds(0.5*x, 5*y, 1.5*x, 1.5*y);
    dryWetKnob.setBounds(8*x, 4.5*y, 2*x, 2*y);

    // bottom sides
    inputGainKnob.setBounds(-0.2*x, 7.5*y, 2*x, 2*y);
    outputGainKnob.setBounds(8*x, 7.5*y, 2*x, 2*y);
    
    

}
