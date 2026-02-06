/*
  ==============================================================================

    ToneStack.cpp
    Created: 6 Feb 2026 3:37:38pm
    Author:  Ramon

  ==============================================================================
*/

#include "ToneStack.h"

void WDFToneStack::prepare(double sampleRate) {
    c6.prepare(sampleRate);
    c7.prepare(sampleRate);
    c8.prepare(sampleRate);
}
inline double WDFToneStack::process(double sample) {

    vs.setVoltage(sample);
    vs.incident(i1.reflected());
    i1.incident(vs.reflected());
    
    return wdft::voltage<double>(s6);
}