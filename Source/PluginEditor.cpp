/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ConjureAudioProcessorEditor::ConjureAudioProcessorEditor (ConjureAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), mMainPanel(p)
{
    setSize (560, 400);
    
    
    addAndMakeVisible (mMainPanel);
}

ConjureAudioProcessorEditor::~ConjureAudioProcessorEditor()
{
}

//==============================================================================
void ConjureAudioProcessorEditor::paint (juce::Graphics& g)
{

}

void ConjureAudioProcessorEditor::resized()
{
    mMainPanel.setBounds (getLocalBounds());
   
}
