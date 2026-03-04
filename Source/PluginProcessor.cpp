#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace
{
constexpr auto driveParamId = "drive";
constexpr auto outputParamId = "output";
}

SuperSoftSoftClipperAudioProcessor::SuperSoftSoftClipperAudioProcessor()
    : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
                                      .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      parameters(*this, nullptr, juce::Identifier("SoftClipperParameters"), createParameterLayout())
{
}

void SuperSoftSoftClipperAudioProcessor::prepareToPlay(double, int)
{
}

void SuperSoftSoftClipperAudioProcessor::releaseResources()
{
}

bool SuperSoftSoftClipperAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
}

void SuperSoftSoftClipperAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    midiMessages.clear();

    const auto driveDb = parameters.getRawParameterValue(driveParamId)->load();
    const auto outputDb = parameters.getRawParameterValue(outputParamId)->load();

    const auto driveLinear = juce::Decibels::decibelsToGain(driveDb);
    const auto outputLinear = juce::Decibels::decibelsToGain(outputDb);

    softClipper.processBlock(buffer, driveLinear, outputLinear);
}

juce::AudioProcessorEditor* SuperSoftSoftClipperAudioProcessor::createEditor()
{
    return new SuperSoftSoftClipperAudioProcessorEditor(*this);
}

bool SuperSoftSoftClipperAudioProcessor::hasEditor() const
{
    return true;
}

const juce::String SuperSoftSoftClipperAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SuperSoftSoftClipperAudioProcessor::acceptsMidi() const
{
    return false;
}

bool SuperSoftSoftClipperAudioProcessor::producesMidi() const
{
    return false;
}

bool SuperSoftSoftClipperAudioProcessor::isMidiEffect() const
{
    return false;
}

double SuperSoftSoftClipperAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SuperSoftSoftClipperAudioProcessor::getNumPrograms()
{
    return 1;
}

int SuperSoftSoftClipperAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SuperSoftSoftClipperAudioProcessor::setCurrentProgram(int)
{
}

const juce::String SuperSoftSoftClipperAudioProcessor::getProgramName(int)
{
    return {};
}

void SuperSoftSoftClipperAudioProcessor::changeProgramName(int, const juce::String&)
{
}

void SuperSoftSoftClipperAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    if (auto xmlState = parameters.state.createXml())
    {
        copyXmlToBinary(*xmlState, destData);
    }
}

void SuperSoftSoftClipperAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    if (const auto xml = getXmlFromBinary(data, sizeInBytes))
    {
        if (xml->hasTagName(parameters.state.getType()))
        {
            parameters.replaceState(juce::ValueTree::fromXml(*xml));
        }
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout SuperSoftSoftClipperAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        driveParamId,
        "Drive",
        juce::NormalisableRange<float>(0.0f, 24.0f, 0.1f),
        6.0f,
        "dB"));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        outputParamId,
        "Output",
        juce::NormalisableRange<float>(-24.0f, 12.0f, 0.1f),
        0.0f,
        "dB"));

    return { params.begin(), params.end() };
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SuperSoftSoftClipperAudioProcessor();
}
