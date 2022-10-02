#pragma once

#include <JuceHeader.h>

class BwLookAndFeel : public juce::LookAndFeel_V4
{
public:
    BwLookAndFeel();

    void drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPos,
                          const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider &) override;
};