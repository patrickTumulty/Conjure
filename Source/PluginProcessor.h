/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Conjure_MidiProcessor.h"

//==============================================================================
/**
*/
class ConjureAudioProcessor  : public juce::AudioProcessor,
                               public juce::ValueTree::Listener
{
public:
    //==============================================================================
    ConjureAudioProcessor();
    ~ConjureAudioProcessor() override;

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
    
    int getRangeHigh();
    int getRangeLow();
    int getRandTempo();
    int getRandSpace();
    juce::String getTempo();
    
    void updateNoteState(); // might not need these
    bool toBool(juce::String val); //
    
    MidiProcessor& getMidiProcessor();
    
    juce::AudioProcessorValueTreeState& getAPVTS() { return mAPVTS; }
    void valueTreePropertyChanged (juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) override;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

private:
    
    
    juce::AudioProcessorValueTreeState mAPVTS;
    std::unique_ptr<MidiProcessor> mMidiProcessor;
    juce::AudioPlayHead::CurrentPositionInfo mInfo;
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConjureAudioProcessor)
};
