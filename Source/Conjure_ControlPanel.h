/*
  ==============================================================================

    Conjure_ControlPanel.h
    Created: 29 Nov 2020 9:30:34pm
    Author:  Patrick Tumulty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Conjure_ControlPanel  : public juce::Component,
                              public juce::Slider::Listener,
                              public juce::ComboBox::Listener
{
public:
    Conjure_ControlPanel(ConjureAudioProcessor& p);
    ~Conjure_ControlPanel() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (juce::Slider *slider) override;
    void comboBoxChanged (juce::ComboBox *comboBoxThatHasChanged) override;
    
    void sliderConfig(juce::Slider* slider, juce::Label* label, juce::String name);

private:
    ConjureAudioProcessor& processor;
    
    juce::Slider mRandTempo;
    juce::Slider mRandSpace;
    juce::Slider mRangeHigh;
    juce::Slider mRangeLow;
    
    juce::Label mRandTempoLabel;
    juce::Label mRandSpaceLabel;
    juce::Label mRangeHighLabel;
    juce::Label mRangeLowLabel;
    juce::Label mTempoSelectLabel;
    
    juce::ComboBox mTempoSelector;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mRandTempoAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mRandSpaceAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mRangeHighAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mRangeLowAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> mTempoAttachment;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Conjure_ControlPanel)
};
