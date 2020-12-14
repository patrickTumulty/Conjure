/*
  ==============================================================================

    Conjure_MidiProcessor.cpp
    Created: 2 Dec 2020 9:57:32am
    Author:  Patrick Tumulty

  ==============================================================================
*/

#include "Conjure_MidiProcessor.h"

MidiProcessor::MidiProcessor() : mAvailableMidiNotes (std::make_unique<juce::SortedSet<int>>()),
                                mSelectedNotesFullRange (std::make_unique<juce::SortedSet<int>>()),
                                mNoteLibrary (std::make_unique<juce::HashMap<juce::String, int>>()),
                                mRandomNumHighValue(0),
                                mCurrentPlaying (0),
                                mUpNext (0),
                                mIsPlaying (false),
                                mKillNotes (false),
                                mRangeHigh (109),
                                mRangeLow (20)
{
    makeNoteLibrary();
    
    
}

MidiProcessor::~MidiProcessor()
{
   
    
}

void MidiProcessor::printNotePool() // for debugging
{
    DBG (" >");
    for (int i = 0; i < mAvailableMidiNotes->size(); i++)
    {
        DBG (mAvailableMidiNotes->getReference(i));
    }
    DBG ("\n");
}

void MidiProcessor::process (juce::MidiBuffer &midiMessages, juce::AudioPlayHead::CurrentPositionInfo &sessionInfo)
{
    mSamplesPerBeat = (60.0 / (sessionInfo.bpm * getTempoScaler())) * mSampleRate;
    mSampleCounter = sessionInfo.timeInSamples % (mSamplesPerBeat);
    
    eventTime = mSampleCounter % mBufferSize;
    if (sessionInfo.isPlaying)
    {
        mKillNotes = true;
        if ((mSampleCounter + mBufferSize) >= mSamplesPerBeat)
        {
            mRandomNumHighValue = mAvailableMidiNotes->size();
            if (mRandomNumHighValue != 0)
            {
                note = mAvailableMidiNotes->getReference (getNextRandomNumber (mRandomNumHighValue-1));
                mCurrentPlaying = mUpNext;
                mUpNext = note;
                if (mCurrentPlaying != 0) { msgOff = juce::MidiMessage::noteOff (1, mCurrentPlaying); }
                msgOn = juce::MidiMessage::noteOn (1, mUpNext, (juce::uint8)100);
                midiMessages.addEvent(msgOff, eventTime);
                midiMessages.addEvent(msgOn, eventTime);
            }
        }
    }
    else
    {
        if (mKillNotes)
        {
            msgOff = juce::MidiMessage::noteOff(1, mUpNext);
            midiMessages.addEvent(msgOff, eventTime);
            mKillNotes = false;
        }
    }
}

int MidiProcessor::getNextRandomNumber(int highValue)
{
    return juce::Random::getSystemRandom().nextInt(highValue);
}

void MidiProcessor::makeNoteLibrary()
{
    mNoteLibrary->set("A",  21);
    mNoteLibrary->set("A#", 22);
    mNoteLibrary->set("B",  23);
    mNoteLibrary->set("C",  24);
    mNoteLibrary->set("C#", 25);
    mNoteLibrary->set("D",  26);
    mNoteLibrary->set("D#", 27);
    mNoteLibrary->set("E",  28);
    mNoteLibrary->set("F",  29);
    mNoteLibrary->set("F#", 30);
    mNoteLibrary->set("G",  31);
    mNoteLibrary->set("G#", 32);
}

void MidiProcessor::updateMidiNotePool()
{
    
}

void MidiProcessor::addNotesToPool (juce::String noteName)
{
    int current_note_value = mNoteLibrary->getReference (noteName);
    while(current_note_value < 109)
    {
        mAvailableMidiNotes->add (current_note_value);
        mSelectedNotesFullRange->add (current_note_value);
        current_note_value += 12;
    }
}

void MidiProcessor::removeNotesFromPool (juce::String noteName)
{
    int current_note_value = mNoteLibrary->getReference (noteName);
    while(current_note_value < 109)
    {
        mAvailableMidiNotes->removeValue (current_note_value);
        mSelectedNotesFullRange->removeValue (current_note_value);
        current_note_value += 12;
    }
}

void MidiProcessor::prepareToPlay()
{
    mNextNote = 50; // why these numbers? Maybe add to intializer list?
    mCurrentNote = 50;
}

void MidiProcessor::setSampleRate (int sampleRate)
{
    mSampleRate = sampleRate;
}

void MidiProcessor::setBufferSize (int bufferSize)
{
    mBufferSize = bufferSize;
}

void MidiProcessor::setIsPlaying (bool value)
{
    mIsPlaying = value;
}

void MidiProcessor::updateRange()
{
    int currentNote;
    
    for (int i = 0; i < mSelectedNotesFullRange->size(); i++)
    {
        currentNote = mSelectedNotesFullRange->getReference (i);
        
        if (mRangeLow <= mRangeHigh)
        {
            if (currentNote < mRangeLow || currentNote > mRangeHigh)
            {
                if (mAvailableMidiNotes->contains (currentNote))
                {
                    mAvailableMidiNotes->removeValue (currentNote);
                }
            }
            else
            {
                if (mAvailableMidiNotes->contains (currentNote) == false)
                {
                    mAvailableMidiNotes->add (currentNote);
                }
            }
        }
        else if (mRangeLow > mRangeHigh)
        {
            if (currentNote > mRangeLow && currentNote < mRangeHigh)
            {
                if (mAvailableMidiNotes->contains (currentNote))
                {
                    mAvailableMidiNotes->removeValue (currentNote);
                }
            }
            else
            {
                if (mAvailableMidiNotes->contains (currentNote) == false)
                {
                    mAvailableMidiNotes->add (currentNote);
                }
            }
        }
    }
}

void MidiProcessor::setRange(int low, int high)
{
    mRangeLow = low;
    mRangeHigh = high;
}

void MidiProcessor::setTempoScaler(float tempoScaler)
{
    mTempoScaler = tempoScaler;
}

float MidiProcessor::getTempoScaler()
{
    return mTempoScaler;
}
