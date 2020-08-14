
#pragma once

#include <JuceHeader.h>

// =============================================================================
// 'Plot' draws a graph within its bounds using a juce::Path object that you
//   must provide.
//
// This class requires:
//   * Path object must consist only of positive points
//   * You must specify a window of your path to display using
//     'setWindow' function
// =============================================================================
class Plot : public juce::Component
{
public:
    // =============================================================================
    // public member functions
    // =============================================================================
    // constructor & destructor
    Plot();
    ~Plot();
    
    // appearance & size
    void paint(juce::Graphics& g) override;
    void resized() override;
    
    // sets the path that this plot will use
    void setPath(const juce::Path& p);
    
    // sets desired window, in the coordinate system of the path you
    // provide via 'setPath' function
    void setWindow(float x1, float x2, float y1, float y2);
    
    // graph appearance set functions
    void setPathStrokeSize(float size);
    void setPathColour(juce::Colour colour);
    void setPathFillColours(juce::Colour top, juce::Colour bottom);
    void setBgColours(juce::Colour top, juce::Colour bottom);
    
private:
    // =============================================================================
    // private member functions
    // =============================================================================
    // create the AffineTransform to transform the input path to one
    // that fits the current bounds and window
    void getTransform();
    
    // resizes a new path and uses it to generate the path that contains
    // the gradient-filled area beneath the path
    void processNewPath(juce::Path& p);
    
    // =============================================================================
    // private member variables
    // =============================================================================
    // Path object representing the magnitude line
    juce::Path magLine;
    
    // Path object representing the fill beneath the line
    juce::Path magFill;
    
    // Colours to define the background gradient, path colour, and
    // path fill gradient
    juce::Colour pathColour{juce::Colours::green};
    juce::Colour fillColourTop{juce::Colours::transparentWhite};
    juce::Colour fillColourBottom{juce::Colours::transparentWhite};
    juce::Colour bgColourTop{juce::Colours::black};
    juce::Colour bgColourBottom{juce::Colours::black};
    
    // these functions generate the background & path fill gradients
    // from the Colours defined above
    juce::ColourGradient getBgColourGradient();
    juce::ColourGradient getFillColourGradient();
    
    // these define the window that is applied to the Path BEFORE it gets
    // scaled to this object's current bounds
    //   i.e. default window has x limits [0,1] and y limits [0,1]
    float xRange = 1.0f;
    float yRange = 1.0f;
    float xStart = 0.0f;
    float yStart = 0.0f;
    
    // transforms input path to current boundary & window conditons
    juce::AffineTransform transform;
    
    // stroke size of the magnitude line
    float pathStrokeSize = 2.0f;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Plot)
    
};
