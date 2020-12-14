/*
  ==============================================================================

    Conjure_MainPanel.h
    Created: 29 Nov 2020 9:15:38pm
    Author:  Patrick Tumulty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Conjure_KeyboardButtons.h"
#include "Conjure_ControlPanel.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Conjure_MainPanel  : public juce::Component
{
public:
    Conjure_MainPanel(ConjureAudioProcessor& p);
    ~Conjure_MainPanel() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    Conjure_KeyboardButtons mKeyboardButtons;
    Conjure_ControlPanel mControlPanel;
    
    juce::Image mBackground;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Conjure_MainPanel)
};
