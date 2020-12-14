/*
  ==============================================================================

    Conjure_KeyboardButtons.cpp
    Created: 29 Nov 2020 9:11:53pm
    Author:  Patrick Tumulty

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Conjure_KeyboardButtons.h"

//==============================================================================
Conjure_KeyboardButtons::Conjure_KeyboardButtons (ConjureAudioProcessor& p) : processor(p)
{
    
    noteSelectButtonConfig (&C_Button, "C");
    noteSelectButtonConfig (&D_Button, "D");
    noteSelectButtonConfig (&E_Button, "E");
    noteSelectButtonConfig (&F_Button, "F");
    noteSelectButtonConfig (&G_Button, "G");
    noteSelectButtonConfig (&A_Button, "A");
    noteSelectButtonConfig (&B_Button, "B");
    
    noteSelectButtonConfig (&CS_Button, "C#");
    noteSelectButtonConfig (&DS_Button, "D#");
    noteSelectButtonConfig (&FS_Button, "F#");
    noteSelectButtonConfig (&GS_Button, "G#");
    noteSelectButtonConfig (&AS_Button, "A#");
    
    C_Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (p.getAPVTS(),    "C",        C_Button);
    CS_Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (p.getAPVTS(),   "C_SHARP",  CS_Button);
    D_Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (p.getAPVTS(),    "D",        D_Button);
    DS_Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (p.getAPVTS(),   "D_SHARP",  DS_Button);
    E_Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (p.getAPVTS(),    "E",        E_Button);
    F_Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (p.getAPVTS(),    "F",        F_Button);
    FS_Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (p.getAPVTS(),   "F_SHARP",  FS_Button);
    G_Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (p.getAPVTS(),    "G",        G_Button);
    GS_Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (p.getAPVTS(),   "G_SHARP",  GS_Button);
    A_Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (p.getAPVTS(),    "A",        A_Button);
    AS_Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (p.getAPVTS(),   "A_SHARP",  AS_Button);
    B_Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (p.getAPVTS(),    "B",        B_Button);

    

}

Conjure_KeyboardButtons::~Conjure_KeyboardButtons()
{
}

void Conjure_KeyboardButtons::paint (juce::Graphics& g)
{
    // ====== KEYBOARD BUTTONS BACKGROUND =====
    
    juce::Rectangle<int> keyboardButtonsBackground = getLocalBounds().reduced (3, 3);
    
//    g.setColour (juce::Colours::darkgrey);
//    g.drawRoundedRectangl (keyboardButtonsBackground.getX(),
//                            keyboardButtonsBackground.getY(),
//                            keyboardButtonsBackground.getWidth(),
//                            keyboardButtonsBackground.getHeight(),
//                            5); // corner
    g.setColour (juce::Colours::lightgoldenrodyellow);
    g.drawRoundedRectangle (keyboardButtonsBackground.getX(),
                           keyboardButtonsBackground.getY(),
                           keyboardButtonsBackground.getWidth(),
                           keyboardButtonsBackground.getHeight(),
                           9, 3); // corner and line thickness
    
}

void Conjure_KeyboardButtons::resized()
{
    juce::Rectangle<int> buttonArea = getLocalBounds().reduced (3,3);
    
    int reducedX = 10;
    int reducedY = 10;
    
    int topRowCoordinateScalarX = (getWidth() / 14);
    int topRowButtonWidth = getWidth() / 7;
    int topRowButtonHeight = getHeight() / 2;
    
    buttonArea = buttonArea.removeFromBottom(getHeight() / 2);
    
    C_Button.setBounds (buttonArea.removeFromLeft (getWidth() / 7).reduced (reducedX, reducedY));
    D_Button.setBounds (buttonArea.removeFromLeft (getWidth() / 7).reduced (reducedX, reducedY));
    E_Button.setBounds (buttonArea.removeFromLeft (getWidth() / 7).reduced (reducedX, reducedY));
    F_Button.setBounds (buttonArea.removeFromLeft (getWidth() / 7).reduced (reducedX, reducedY));
    G_Button.setBounds (buttonArea.removeFromLeft (getWidth() / 7).reduced (reducedX, reducedY));
    A_Button.setBounds (buttonArea.removeFromLeft (getWidth() / 7).reduced (reducedX, reducedY));
    B_Button.setBounds (buttonArea.removeFromLeft (getWidth() / 7).reduced (reducedX, reducedY));
    
    CS_Button.setBounds (juce::Rectangle<int> (topRowCoordinateScalarX * 1, 5, topRowButtonWidth, topRowButtonHeight).reduced (reducedX, reducedY));
    DS_Button.setBounds (juce::Rectangle<int> (topRowCoordinateScalarX * 3, 5, topRowButtonWidth, topRowButtonHeight).reduced (reducedX, reducedY));
    
    FS_Button.setBounds (juce::Rectangle<int> (topRowCoordinateScalarX * 7, 5, topRowButtonWidth, topRowButtonHeight).reduced (reducedX, reducedY));
    GS_Button.setBounds (juce::Rectangle<int> (topRowCoordinateScalarX * 9, 5, topRowButtonWidth, topRowButtonHeight).reduced (reducedX, reducedY));
    AS_Button.setBounds (juce::Rectangle<int> (topRowCoordinateScalarX * 11, 5, topRowButtonWidth, topRowButtonHeight).reduced (reducedX, reducedY));

}

void Conjure_KeyboardButtons::noteSelectButtonConfig (juce::TextButton* button, juce::String noteName)
{
//    button->setButtonText (noteName); // Commented out because text overlaps in the way that buttons are drawn
    button->setClickingTogglesState (true);
    button->setColour (juce::TextButton::ColourIds::buttonColourId, juce::Colours::mediumpurple);
    button->setColour (juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::yellow);
    button->setColour (juce::TextButton::ColourIds::textColourOnId, juce::Colours::black);
    button->setColour (juce::TextButton::ColourIds::textColourOffId, juce::Colours::dimgrey);
    button->addListener (this);
    button->setName (noteName);
    addAndMakeVisible (button);
}

void Conjure_KeyboardButtons::buttonClicked (juce::Button *button)
{
    if (button->getToggleState())
        processor.getMidiProcessor().addNotesToPool (button->getName());
    else
        processor.getMidiProcessor().removeNotesFromPool (button->getName());
    processor.getMidiProcessor().updateRange();
    processor.getMidiProcessor().printNotePool();
}

void Conjure_KeyboardButtons::buttonStateChanged (juce::Button *button)
{
   
    
}
