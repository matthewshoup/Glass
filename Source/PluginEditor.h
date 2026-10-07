#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
class GlassAudioProcessorEditor:public juce::AudioProcessorEditor{public:explicit GlassAudioProcessorEditor(GlassAudioProcessor&);void paint(juce::Graphics&)override;void resized()override;private:GlassAudioProcessor&p;juce::Slider drive,character,bias,mix,output;juce::ToggleButton original{"ORIGINAL CIRCUIT"};using SA=juce::AudioProcessorValueTreeState::SliderAttachment;using BA=juce::AudioProcessorValueTreeState::ButtonAttachment;std::unique_ptr<SA>a1,a2,a3,a4,a5;std::unique_ptr<BA>a6;void knob(juce::Slider&,const juce::String&);JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GlassAudioProcessorEditor)};
