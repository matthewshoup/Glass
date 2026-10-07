#pragma once
#include <JuceHeader.h>
#include "TubeStage.h"
class GlassAudioProcessor : public juce::AudioProcessor {
public:
 GlassAudioProcessor();
 void prepareToPlay(double,int) override; void releaseResources() override {}
 bool isBusesLayoutSupported(const BusesLayout&) const override;
 void processBlock(juce::AudioBuffer<float>&,juce::MidiBuffer&) override;
 juce::AudioProcessorEditor* createEditor() override; bool hasEditor() const override{return true;}
 const juce::String getName() const override{return "Glass";}
 bool acceptsMidi() const override{return false;} bool producesMidi() const override{return false;} bool isMidiEffect() const override{return false;}
 double getTailLengthSeconds() const override{return 0;}
 int getNumPrograms() override{return 1;} int getCurrentProgram() override{return 0;} void setCurrentProgram(int) override{}
 const juce::String getProgramName(int) override{return {};} void changeProgramName(int,const juce::String&) override{}
 void getStateInformation(juce::MemoryBlock&) override; void setStateInformation(const void*,int) override;
 juce::AudioProcessorValueTreeState apvts;
private:
 static juce::AudioProcessorValueTreeState::ParameterLayout layout(); TubeStage tube[2];
 JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GlassAudioProcessor)
};