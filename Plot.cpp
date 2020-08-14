
#include "Plot.h"

// constructor & destructor
Plot::Plot() {}
Plot::~Plot() {}

// paint & resized
void Plot::paint(juce::Graphics& g) {
    g.setGradientFill(getBgColourGradient());
    g.fillAll();
    
    g.setGradientFill(getFillColourGradient());
    g.fillPath(magFill);
    
    g.setColour(pathColour);
    g.strokePath(magLine, juce::PathStrokeType(pathStrokeSize, juce::PathStrokeType::JointStyle::curved));
}
void Plot::resized() {
    getTransform();
}

void Plot::setPath(const juce::Path& p) {
    // save the path and scale it to fit the current dimensions
    magLine = p;
    processNewPath(magLine);
}

void Plot::setWindow(float x1, float x2, float y1, float y2) {
    // save the window settings as origin & range
    xRange = x2 - x1;
    yRange = y2 - y1;
    xStart = x1;
    yStart = y1;
    
    // update the AffineTransform
    getTransform();
}

// graph appearance stuff
void Plot::setPathStrokeSize(float size) {
    pathStrokeSize = size;
    repaint();
}
void Plot::setPathColour(juce::Colour colour) {
    pathColour = colour;
    repaint();
}
void Plot::setPathFillColours(juce::Colour top, juce::Colour bottom) {
    fillColourTop = top;
    fillColourBottom = bottom;
}
void Plot::setBgColours(juce::Colour top, juce::Colour bottom) {
    bgColourTop = top;
    bgColourBottom = bottom;
    repaint();
}

void Plot::getTransform() {
    // translate so that (xStart, yStart) is the new origin
    transform = juce::AffineTransform::translation(-xStart, -yStart);
    
    // scale the x&y axes so that the desired range appears in the current bounds
    transform = transform.scaled(getWidth()/xRange, getHeight()/yRange);

    // flip the path so it displays correctly
    transform = transform.followedBy(juce::AffineTransform::verticalFlip(getHeight()));
}

void Plot::processNewPath(juce::Path& p) {
    // scale the magnitude curve to fit in the current bounds
    p.applyTransform(transform);
    
    // create the filled path from the scaled magnitude curve
    //  ** this assumes that magLine is filled in from left to right **
    magFill = p;
    auto lastPoint = magFill.getCurrentPosition();
    magFill.lineTo(lastPoint.getX(), getHeight());
    magFill.lineTo(0, getHeight());
    magFill.closeSubPath();
    
    repaint();
}

// gradients
juce::ColourGradient Plot::getFillColourGradient() {
    return juce::ColourGradient(fillColourTop, 0, 0,
                                fillColourBottom, 0, getHeight(),
                                false);
}
juce::ColourGradient Plot::getBgColourGradient() {
    return juce::ColourGradient(bgColourTop, 0, 0,
                                bgColourBottom, 0, getHeight(),
                                false);
}
