#pragma once
#include <JuceHeader.h>
#include <cmath>
#include "CircuitCalibration.h"
class TubeStage {
public:
 void prepare(double sr){sampleRate=juce::jmax(8000.0,sr); reset();}
 void reset(){cathode=sag=gridMemory=flux=lp=x1=y1=0.0f;}
 float process(float x,float driveDb,float character,float bias,bool circuit){
   float drive=juce::Decibels::decibelsToGain(driveDb);
   float nominalCathode=cal.idlePlateCurrentmA*.001f*cal.cathodeResistorOhms;
   float vgk=cal.nominalGridSwingVolts*x*drive-nominalCathode+bias*18.0f;
   if(circuit){
     float over=juce::jmax(0.0f,vgk-cal.gridCurrentKneeVolts);
     float ig=cal.gridCurrentScale*softplus(over/5.0f);
     float drop=ig*cal.sourceResistanceOhms;
     gridMemory=onePole(gridMemory,drop,.0015f); vgk-=drop+.1f*gridMemory;
   }
   float e=(vgk+nominalCathode)/juce::jmax(20.0f,cal.nominalGridSwingVolts);
   float asym=.11f+.22f*character;
   float n=std::tanh(1.45f*e+asym*e*e)+.035f*character*e*e*e;
   float plateA=cal.idlePlateCurrentmA*.001f*(1.0f+.95f*n);
   if(circuit){
     float tau=juce::jmax(.001f,cal.cathodeResistorOhms*cal.cathodeCapuF*1e-6f);
     cathode=onePole(cathode,plateA*cal.cathodeResistorOhms-nominalCathode,tau);
     n-=cathode/juce::jmax(20.0f,cal.nominalGridSwingVolts);
     float st=juce::jmax(.001f,cal.supplyResistanceOhms*cal.supplyCapuF*1e-6f);
     float excess=juce::jmax(0.0f,plateA-cal.idlePlateCurrentmA*.001f);
     sag=onePole(sag,excess*cal.supplyResistanceOhms,st);
     n*=juce::jlimit(.45f,1.0f,(cal.bPlusVolts-sag)/juce::jmax(1.0f,cal.bPlusVolts));
     n=transformer(n,plateA);
   }
   float r=std::exp(-2.0f*juce::MathConstants<float>::pi*10.0f/(float)sampleRate);
   float hp=n-x1+r*y1; x1=n; y1=hp;
   return std::tanh(hp*.94f);
 }
private:
 float softplus(float x){if(x>12)return x;if(x<-12)return std::exp(x);return std::log1p(std::exp(x));}
 float onePole(float s,float t,float sec){float a=std::exp(-1.0f/((float)sampleRate*sec));return a*s+(1-a)*t;}
 float transformer(float x,float plateA){
   float lf=juce::jmax(2.0f,cal.primaryLoadOhms/(2.0f*juce::MathConstants<float>::pi*juce::jmax(.1f,cal.primaryInductanceH)));
   float fa=std::exp(-2.0f*juce::MathConstants<float>::pi*lf/(float)sampleRate);
   float satA=juce::jmax(.010f,cal.saturationCurrentmA*.001f);
   flux=fa*flux+(1-fa)*x;
   float core=std::tanh(x+.20f*flux+.22f*(plateA/satA)*flux);
   float leak=juce::jmax(1e-5f,cal.leakageInductancemH*.001f);
   float hf=juce::jlimit(8000.0f,80000.0f,cal.primaryLoadOhms/(2.0f*juce::MathConstants<float>::pi*leak));
   float a=std::exp(-2.0f*juce::MathConstants<float>::pi*hf/(float)sampleRate);
   lp=a*lp+(1-a)*core;
   return lp*cal.primaryLoadOhms/juce::jmax(1.0f,cal.primaryLoadOhms+cal.windingResistanceOhms);
 }
 double sampleRate=44100.0; CircuitCalibration cal; float cathode=0,sag=0,gridMemory=0,flux=0,lp=0,x1=0,y1=0;
};