/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Conjure_MainPanel.h"

//==============================================================================
/**
*/
class ConjureAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ConjureAudioProcessorEditor (ConjureAudioProcessor&);
    ~ConjureAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ConjureAudioProcessor& audioProcessor;
    
    Conjure_MainPanel mMainPanel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConjureAudioProcessorEditor)
};
