

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ConjureAudioProcessor::ConjureAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), mAPVTS(*this, nullptr, "PARAMETERS", createParameters()),
                        mMidiProcessor (std::make_unique<MidiProcessor>())
#endif
{
    mAPVTS.state.addListener (this);
    
    
}

ConjureAudioProcessor::~ConjureAudioProcessor()
{
}

//==============================================================================
const juce::String ConjureAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ConjureAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ConjureAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ConjureAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ConjureAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ConjureAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ConjureAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ConjureAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ConjureAudioProcessor::getProgramName (int index)
{
    return {};
}

void ConjureAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ConjureAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mMidiProcessor->prepareToPlay();
    mMidiProcessor->setBufferSize (samplesPerBlock);
    mMidiProcessor->setSampleRate (sampleRate);
}

void ConjureAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ConjureAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ConjureAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    buffer.clear();
    midiMessages.clear();
    
    getPlayHead()->getCurrentPosition (mInfo);
    mMidiProcessor->process (midiMessages, mInfo);
    

    
}

//==============================================================================
bool ConjureAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ConjureAudioProcessor::createEditor()
{
    return new ConjureAudioProcessorEditor (*this);
}

//==============================================================================
void ConjureAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ConjureAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

juce::AudioProcessorValueTreeState::ParameterLayout ConjureAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;
    
    parameters.push_back (std::make_unique<juce::AudioParameterInt> ("RANGE_LOW", "Range Low", 21, 108, 21));
    parameters.push_back (std::make_unique<juce::AudioParameterInt> ("RANGE_HIGH", "Range High", 21, 108, 108));
    parameters.push_back (std::make_unique<juce::AudioParameterInt> ("RAND_TEMPO", "Random Tempo", 0, 99, 0));
    parameters.push_back (std::make_unique<juce::AudioParameterInt> ("RAND_SPACE", "Random Space", 0, 99, 0));
    parameters.push_back (std::make_unique<juce::AudioParameterChoice> ("TEMPO", "Tempo",
                                                                       juce::StringArray { "1/1", "1/2", "1/4", "1/8", "1/16", "1/32" },
                                                                       2));
    parameters.push_back (std::make_unique<juce::AudioParameterBool> ("C",          "c", false));
    parameters.push_back (std::make_unique<juce::AudioParameterBool> ("C_SHARP",    "c#", false));
    parameters.push_back (std::make_unique<juce::AudioParameterBool> ("D",          "d", false));
    parameters.push_back (std::make_unique<juce::AudioParameterBool> ("D_SHARP",    "d#", false));
    parameters.push_back (std::make_unique<juce::AudioParameterBool> ("E",          "e", false));
    parameters.push_back (std::make_unique<juce::AudioParameterBool> ("F",          "f", false));
    parameters.push_back (std::make_unique<juce::AudioParameterBool> ("F_SHARP",    "f#", false));
    parameters.push_back (std::make_unique<juce::AudioParameterBool> ("G",          "g", false));
    parameters.push_back (std::make_unique<juce::AudioParameterBool> ("G_SHARP",    "g#", false));
    parameters.push_back (std::make_unique<juce::AudioParameterBool> ("A",          "a", false));
    parameters.push_back (std::make_unique<juce::AudioParameterBool> ("A_SHARP",    "a#", false));
    parameters.push_back (std::make_unique<juce::AudioParameterBool> ("B",          "b", false));

    
    return { parameters.begin(), parameters.end() };
}

int ConjureAudioProcessor::getRangeLow()
{
    return mAPVTS.getRawParameterValue("RANGE_LOW")->load();
}

int ConjureAudioProcessor::getRangeHigh()
{
    return mAPVTS.getRawParameterValue("RANGE_HIGH")->load();
}

int ConjureAudioProcessor::getRandSpace()
{
    return mAPVTS.getRawParameterValue("RAND_SPACE")->load();
}

int ConjureAudioProcessor::getRandTempo()
{
    return mAPVTS.getRawParameterValue("RAND_TEMPO")->load();
}

juce::String ConjureAudioProcessor::getTempo()
{
    return mAPVTS.getParameter("TEMPO")->getCurrentValueAsText();
}


bool ConjureAudioProcessor::toBool(juce::String val)
{
    if (val == "On")
        return true;
    return false;
}

void ConjureAudioProcessor::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
{
//    DBG(mAPVTS.getParameter("C")->getCurrentValueAsText());
  
    
}

MidiProcessor& ConjureAudioProcessor::getMidiProcessor()
{
    return *mMidiProcessor;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ConjureAudioProcessor();
}
