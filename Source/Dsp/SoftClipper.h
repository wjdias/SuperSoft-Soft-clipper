#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <cmath>

namespace supersoft::dsp
{
class SoftClipper
{
public:
    void processBlock(juce::AudioBuffer<float>& buffer, float driveLinear, float outputLinear)
    {
        const auto channels = buffer.getNumChannels();
        const auto samples = buffer.getNumSamples();

        for (int channel = 0; channel < channels; ++channel)
        {
            auto* data = buffer.getWritePointer(channel);

            for (int i = 0; i < samples; ++i)
            {
                const float driven = data[i] * driveLinear;
                data[i] = std::tanh(driven) * outputLinear;
            }
        }
    }
};
} // namespace supersoft::dsp
