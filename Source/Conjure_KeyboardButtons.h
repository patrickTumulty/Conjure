/*
  ==============================================================================

    Conjure_KeyboardButtons.h
    Created: 29 Nov 2020 9:11:53pm
    Author:  Patrick Tumulty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


//==============================================================================
/*
*/
class Conjure_KeyboardButtons  : public juce::Component,
                                 public juce::Button::Listener
{
public:
    Conjure_KeyboardButtons(ConjureAudioProcessor& p);
    ~Conjure_KeyboardButtons() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void buttonClicked (juce::Button* button) override;
    void buttonStateChanged (juce::Button* button) override;
    
    
    void noteSelectButtonConfig(juce::TextButton* button, juce::String noteName);

private:
    ConjureAudioProcessor& processor;
    
    juce::TextButton C_Button;
    juce::TextButton CS_Button;
    juce::TextButton D_Button;
    juce::TextButton DS_Button;
    juce::TextButton E_Button;
    juce::TextButton F_Button;
    juce::TextButton FS_Button;
    juce::TextButton G_Button;
    juce::TextButton GS_Button;
    juce::TextButton A_Button;
    juce::TextButton AS_Button;
    juce::TextButton B_Button;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> C_Attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> CS_Attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> D_Attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> DS_Attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> E_Attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> F_Attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> FS_Attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> G_Attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> GS_Attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> A_Attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> AS_Attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> B_Attachment;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Conjure_KeyboardButtons)
};
