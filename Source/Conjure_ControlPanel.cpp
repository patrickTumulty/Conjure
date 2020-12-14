/*
  ==============================================================================

    Conjure_ControlPanel.cpp
    Created: 29 Nov 2020 9:30:34pm
    Author:  Patrick Tumulty

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Conjure_ControlPanel.h"

//==============================================================================
Conjure_ControlPanel::Conjure_ControlPanel(ConjureAudioProcessor& p) : processor(p)
{
    
    // === Rotary Sliders ===
    
    sliderConfig (&mRandTempo, &mRandTempoLabel, "T");
    mRandTempo.setTextValueSuffix ("%");
    sliderConfig (&mRandSpace, &mRandSpaceLabel, "S");
    mRandSpace.setTextValueSuffix ("%");
    sliderConfig (&mRangeHigh, &mRangeHighLabel, "H");
    mRangeHigh.setColour (juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::mediumpurple);
    mRangeHigh.setColour (juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::palevioletred);
    sliderConfig (&mRangeLow, &mRangeLowLabel, "L");
    
    // === Tempo Selector ===
    
    addAndMakeVisible (mTempoSelector);
    mTempoSelector.addItemList (juce::StringArray { "1/1", "1/2", "1/4", "1/8", "1/16", "1/32" }, 1);
    mTempoSelector.setSelectedId (3); // start with 1/4
    mTempoSelector.setColour (juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::mediumpurple);
    mTempoSelector.setColour (juce::ComboBox::ColourIds::arrowColourId, juce::Colours::lightyellow);
    mTempoSelector.setColour (juce::ComboBox::ColourIds::textColourId, juce::Colours::ghostwhite);
    mTempoSelector.addListener (this);
    
    // === Tempo Selector Label ===
    
    addAndMakeVisible (mTempoSelectLabel);
    mTempoSelectLabel.setJustificationType (juce::Justification::centredTop);
    mTempoSelectLabel.setColour (juce::Label::textColourId, juce::Colours::ghostwhite);
    mTempoSelectLabel.setText ("Tempo", juce::dontSendNotification);
    mTempoSelectLabel.setFont (juce::Font ("Arial", 16.0f, juce::Font::FontStyleFlags::bold));
    
    // === APVTS Attachments ===
    
    mRandSpaceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p.getAPVTS(), "RAND_SPACE", mRandSpace);
    mRandTempoAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p.getAPVTS(), "RAND_TEMPO", mRandTempo);
    mRangeHighAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p.getAPVTS(), "RANGE_HIGH", mRangeHigh);
    mRandSpaceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p.getAPVTS(), "RANGE_LOW", mRangeLow);
    mTempoAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(p.getAPVTS(), "TEMPO", mTempoSelector);
}

Conjure_ControlPanel::~Conjure_ControlPanel()
{
}

void Conjure_ControlPanel::paint (juce::Graphics& g)
{
    
}

void Conjure_ControlPanel::resized()
{
    
    juce::Rectangle<int> localBounds = getLocalBounds();
    juce::Rectangle<int> labelBounds = localBounds.removeFromBottom (getHeight() / 6);
    int rY = 0;
    
    // === Controls ===
    
    mRandTempo.setBounds (localBounds.removeFromLeft (getWidth() / 5).reduced (0, rY));
    mRandSpace.setBounds (localBounds.removeFromLeft (getWidth() / 5).reduced (0, rY));
    mTempoSelector.setBounds (localBounds.removeFromLeft (getWidth() / 5).reduced (5, 35));
    mRangeLow.setBounds (localBounds.removeFromLeft (getWidth() / 5).reduced (0, rY));
    mRangeHigh.setBounds (localBounds.reduced (0, rY));
    
    // === Labels === 
    
    mRandTempoLabel.setBounds (labelBounds.removeFromLeft(getWidth() / 5));
    mRandSpaceLabel.setBounds (labelBounds.removeFromLeft(getWidth() / 5));
    mTempoSelectLabel.setBounds (labelBounds.removeFromLeft(getWidth() / 5));
    mRangeLowLabel.setBounds (labelBounds.removeFromLeft(getWidth() / 5));
    mRangeHighLabel.setBounds (labelBounds);
    
}

void Conjure_ControlPanel::sliderConfig(juce::Slider* slider, juce::Label* label, juce::String name)
{
    
    // === Slider Config ===
    
    addAndMakeVisible (slider);
    slider->setSliderStyle (juce::Slider::SliderStyle::Rotary);
    slider->setTextBoxStyle (juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    slider->setColour (juce::Slider::ColourIds::thumbColourId, juce::Colours::yellow);
    slider->setColour (juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::palevioletred);
    slider->setColour (juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::mediumpurple);
    slider->setColour (juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    slider->addListener (this);
    
    // === Label Config ===
    
    addAndMakeVisible (label);
    label->setJustificationType (juce::Justification::centredTop);
    label->setColour(juce::Label::textColourId, juce::Colours::ghostwhite);
    label->setText (name, juce::dontSendNotification);
    label->setFont (juce::Font ("Arial", 16.0f, juce::Font::FontStyleFlags::bold));
    
}


void  Conjure_ControlPanel::sliderValueChanged (juce::Slider *slider)
{
    if (slider == &mRangeLow || slider == &mRangeHigh)
    {
        processor.getMidiProcessor().setRange (processor.getRangeLow(), processor.getRangeHigh());
        processor.getMidiProcessor().updateRange();
    }
}

void Conjure_ControlPanel::comboBoxChanged (juce::ComboBox *comboBoxThatHasChanged)
{
    juce::String tempo = comboBoxThatHasChanged->getText();
    if (tempo == "1/1") { processor.getMidiProcessor().setTempoScaler (0.25f); }
    else if (tempo == "1/2" )   { processor.getMidiProcessor().setTempoScaler (0.5f); }
    else if (tempo == "1/4" )   { processor.getMidiProcessor().setTempoScaler (1.0f); }
    else if (tempo == "1/8" )   { processor.getMidiProcessor().setTempoScaler (2.0f); }
    else if (tempo == "1/16" )  { processor.getMidiProcessor().setTempoScaler (4.0f); }
    else if (tempo == "1/32" )  { processor.getMidiProcessor().setTempoScaler (8.0f); }
}
