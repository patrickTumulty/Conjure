/*
  ==============================================================================

    Conjure_MidiProcessor.h
    Created: 2 Dec 2020 9:57:32am
    Author:  Patrick Tumulty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <iostream>



class MidiProcessor
{
public:
    MidiProcessor();
    ~MidiProcessor();
    
    
    
    void process(juce::MidiBuffer& midiMessages, juce::AudioPlayHead::CurrentPositionInfo& sessionInfo);
    void setSampleRate(int sampleRate);
    void setBufferSize(int bufferSize);
    void prepareToPlay();
    void setRange(int low, int high);
    
    void makeNoteLibrary();
    void updateMidiNotePool();
    void removeNotesFromPool(juce::String noteName);
    void addNotesToPool(juce::String noteName);
    void printNotePool();
    int getNextRandomNumber(int highValue);
    void setIsPlaying(bool value);
    
    void setTempoScaler(float tempoScaler);
    float getTempoScaler();
    
    void updateRange();
    
    
    
private:
    int mRandomNumHighValue;
    
    int mSampleRate; // set in prepare to play
    int mBufferSize;
    
    int mCurrentNote;
    int mNextNote;
    
    int mCurrentPlaying;
    int mUpNext;
    int note;
    
    // Set of available notes
    std::unique_ptr<juce::SortedSet<int>> mAvailableMidiNotes;
    
    // Set of selected notes
    // No range parameter
    std::unique_ptr<juce::SortedSet<int>> mSelectedNotesFullRange;
    
    // Map of note to midi valueu
    std::unique_ptr<juce::HashMap<juce::String, int>> mNoteLibrary;
    
    int mTotalSamples;
    int mSamplesPerBeat;
    int mSampleCounter;
 
    int eventTime;
    
    bool mIsPlaying;
    bool mKillNotes;
    
    int mRangeHigh;
    int mRangeLow;
    
    float mTempoScaler { 1.0f };
    int mScaledBPM;
    
    juce::MidiMessage msgOn;
    juce::MidiMessage msgOff;
    
};
