/*
  ==============================================================================

    Conjure_MainPanel.cpp
    Created: 29 Nov 2020 9:15:38pm
    Author:  Patrick Tumulty

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Conjure_MainPanel.h"

//==============================================================================
Conjure_MainPanel::Conjure_MainPanel(ConjureAudioProcessor& p) : mKeyboardButtons(p), mControlPanel(p)
{
    mBackground = juce::ImageCache::getFromMemory(BinaryData::Conjure_BackgroundV24x_png, BinaryData::Conjure_BackgroundV24x_pngSize);
    
    addAndMakeVisible (mKeyboardButtons);
    addAndMakeVisible (mControlPanel);

}

Conjure_MainPanel::~Conjure_MainPanel()
{
}

void Conjure_MainPanel::paint (juce::Graphics& g)
{
    g.drawImage (mBackground, juce::Rectangle<float> (0,0,getWidth(), getHeight()));
    
}

void Conjure_MainPanel::resized()
{
    juce::Rectangle<int> localBounds = getLocalBounds();
    mControlPanel.setBounds (localBounds.removeFromBottom (getHeight() / 3));
    mKeyboardButtons.setBounds (localBounds.removeFromBottom (getHeight() / 2).reduced (5, 5));

}
