#include "PluginEditor.h"

SuperSoftSoftClipperAudioProcessorEditor::SuperSoftSoftClipperAudioProcessorEditor(SuperSoftSoftClipperAudioProcessor& p)
    : AudioProcessorEditor(&p),
      processorRef(p)
{
    setSize(360, 180);

    auto configureSlider = [this](juce::Slider& slider, juce::Label& label, const juce::String& text)
    {
        slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
        addAndMakeVisible(slider);

        label.setText(text, juce::dontSendNotification);
        label.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(label);
    };

    configureSlider(driveSlider, driveLabel, "Drive");
    configureSlider(outputSlider, outputLabel, "Output");

    driveAttachment = std::make_unique<SliderAttachment>(processorRef.parameters, "drive", driveSlider);
    outputAttachment = std::make_unique<SliderAttachment>(processorRef.parameters, "output", outputSlider);
}

void SuperSoftSoftClipperAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff202225));

    g.setColour(juce::Colour(0xfff2f2f2));
    g.setFont(juce::FontOptions(24.0f, juce::Font::bold));
    g.drawFittedText("SuperSoft Soft Clipper", getLocalBounds().removeFromTop(40), juce::Justification::centred, 1);
}

void SuperSoftSoftClipperAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds().reduced(20);
    bounds.removeFromTop(40);

    auto row = bounds.removeFromTop(120);
    auto left = row.removeFromLeft(row.getWidth() / 2);

    driveLabel.setBounds(left.removeFromTop(20));
    driveSlider.setBounds(left.reduced(10));

    outputLabel.setBounds(row.removeFromTop(20));
    outputSlider.setBounds(row.reduced(10));
}
