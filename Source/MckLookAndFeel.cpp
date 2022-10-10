#include "MckLookAndFeel.hpp"

MckLookAndFeel::MckLookAndFeel()
{
    ColourScheme cs = {
        0xff2a2a2a,     // windowBackground
        0xff333333,     // widgetBackground
        0xff333333,     // menuBackground
        0xff3a3a3a,     // outline
        0xfff0f0f0,     // defaultText
        0xfff0f0f0,     // defaultFill
        0xfff0f0f0,     // highlightedText
        0xff009bb3,     // highlightedFill
        0xffffffff};    // menuText

    setColourScheme(cs);

    setColour(juce::TextButton::textColourOnId, juce::Colour::fromRGB(32,32,32));
    
    Typeface::Ptr tface = Typeface::createSystemTypefaceFor(BinaryData::LatoBold_ttf, BinaryData::LatoBold_ttfSize);
    setDefaultSansSerifTypeface(tface);

    // setColour(juce::DocumentWindow::backgroundColourId, juce::Colour::fromRGB(42, 42, 42));
    // setColour(windowBac)
    // setColour(juce::Label::textColourId, juce::Colour::fromRGB(0, 155, 179));
}

void MckLookAndFeel::drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPos,
                                      const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider &s)
{
    auto size = (float)juce::jmin(width / 2, height / 2);
    auto knobRadius = 0.75f * size;
    auto radius = size - 4.0f;
    auto centreX = (float)x + (float)width * 0.5f;
    auto centreY = (float)y + (float)height * 0.5f;
    auto rx = centreX - knobRadius;
    auto ry = centreY - knobRadius;
    auto rw = knobRadius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // auto hlColour = juce::Colour::fromRGB(0, 66, 76);
    auto bgColour = juce::Colour::fromRGB(58, 58, 58);
    auto bgAlt = juce::Colour::fromRGB(42, 42, 42);
    auto shade1 = juce::Colour::fromRGB(74, 74, 74);
    auto shade2 = juce::Colour::fromRGB(90, 90, 90);
    auto shade3 = juce::Colour::fromRGB(160, 160, 160);
    auto ringColour = juce::Colour::fromRGB(200, 200, 200);
    auto ringHlColour = juce::Colour::fromRGB(0, 155, 179);

    auto hlColour = juce::Colour::fromRGB(0, 155, 179);
    auto hlShade1 = juce::Colour::fromRGB(0, 66, 76);
    auto hlShade2 = juce::Colour::fromRGB(0, 43, 51);

    // Knob Fill
    juce::ColourGradient grad(shade1, juce::Point<float>(centreX, centreY), bgAlt, juce::Point<float>(rx, ry), true);
    g.setGradientFill(grad);
    g.fillEllipse(rx, ry, rw, rw);

    auto outlineThickness = std::ceil(size / 50.0f);

    // pointer
    juce::Path p1;
    auto pointerLength = knobRadius * 0.75f;
    auto pointerThickness = size / 10.0f;
    p1.addRoundedRectangle(-pointerThickness * 0.5f, -knobRadius, pointerThickness, pointerLength + pointerThickness, pointerThickness / 2.0f);
    p1.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

    g.setColour(hlColour);
    g.fillPath(p1);

    juce::Path p4;
    auto p4Thickness = size / 20.0f;
    p4.addRectangle(-p4Thickness * 0.5f, -knobRadius, p4Thickness, pointerLength + pointerThickness - p4Thickness / 2.0f);
    p4.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

    // g.setColour(hlColour);
    // g.fillPath(p4);

    // outline
    g.setColour(shade2);
    g.drawEllipse(rx + outlineThickness * 0.5f, ry + outlineThickness * 0.5f, rw - outlineThickness, rw - outlineThickness, outlineThickness);

    // Path
    auto pathThickness = pointerThickness;
    auto pathRadius = size - pointerThickness / 2.0f;

    juce::Path p2;
    p2.addCentredArc(centreX, centreY, pathRadius, pathRadius, 0, rotaryStartAngle, rotaryEndAngle, true);
    PathStrokeType(pointerThickness, juce::PathStrokeType::JointStyle::curved, juce::PathStrokeType::EndCapStyle::rounded).createStrokedPath(p2, p2);

    g.setColour(shade2);
    g.fillPath(p2);

    // g.setColour(hlShade2);
    // g.fillPath(p2);

    juce::Path p3;
    auto curAngle = rotaryStartAngle + (rotaryEndAngle - rotaryStartAngle) * sliderPos;
    if (s.isSymmetricSkew()) {
        auto rotaryMidAngle = rotaryStartAngle + (rotaryEndAngle - rotaryStartAngle) / 2.0f;
        if (std::abs(curAngle - rotaryMidAngle) < M_PI / 180.0) {
            p3.addCentredArc(centreX, centreY, pathRadius, pathRadius, 0, rotaryMidAngle - M_PI / 180.0, rotaryMidAngle + M_PI / 180.0, true);
        } else {
            p3.addCentredArc(centreX, centreY, pathRadius, pathRadius, 0, curAngle, rotaryMidAngle, true);
        }
    } else {
    p3.addCentredArc(centreX, centreY, pathRadius, pathRadius, 0, rotaryStartAngle, curAngle, true);
    }
    PathStrokeType(pointerThickness, juce::PathStrokeType::JointStyle::curved, juce::PathStrokeType::EndCapStyle::rounded).createStrokedPath(p3, p3);
    g.setColour(hlColour);
    g.fillPath(p3);
}

void MckLookAndFeel::fillResizableWindowBackground(juce::Graphics &g,
                                                   int width,
                                                   int height,
                                                   const juce::BorderSize<int> &borderSize,
                                                   juce::ResizableWindow &window)
{
    g.setColour(juce::Colour::fromRGB(58, 58, 58));
    g.fillRect(0, 0, width, height);
}