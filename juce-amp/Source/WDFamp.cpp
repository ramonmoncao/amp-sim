/*
  ==============================================================================

    WDFamp.cpp
    Created: 5 Feb 2026 9:38:17pm
    Author:  Ramon

  ==============================================================================
*/

#include "WDFamp.h"

void WDFamp::prepare(double sampleRate)
{
    c4.prepare(sampleRate);
}
inline StageVoltages WDFamp::processStageU1(double sample)
{
    vs.setVoltage(sample);
	s2.incident(p1.reflected());
    StageVoltages voltages;
	voltages.grid = wdft::voltage<double>(r7);
	voltages.cathode = wdft::voltage<double>(p1);
    p1.incident(s2.reflected());
    
    return voltages;
}
inline StageVoltages WDFamp::processStageU2(double sample)
{
    vs2.setVoltage(sample);
    vs2.incident(i1.reflected());
	StageVoltages voltages;
	voltages.grid = wdft::voltage<double>(r3);
	voltages.cathode = wdft::voltage<double>(p2);
    i1.incident(vs2.reflected());
    return voltages ;
}