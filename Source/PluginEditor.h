#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include "PluginProcessor.h"

class SuperSoftSoftClipperAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit SuperSoftSoftClipperAudioProcessorEditor(SuperSoftSoftClipperAudioProcessor&);
    ~SuperSoftSoftClipperAudioProcessorEditor() override = default;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    SuperSoftSoftClipperAudioProcessor& processorRef;

    juce::Slider driveSlider;
    juce::Slider outputSlider;

    juce::Label driveLabel;
    juce::Label outputLabel;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> driveAttachment;
    std::unique_ptr<SliderAttachment> outputAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SuperSoftSoftClipperAudioProcessorEditor)
};
