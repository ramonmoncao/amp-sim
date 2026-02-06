/*
  ==============================================================================

    WDFPreAmp.cpp
    Created: 5 Feb 2026 9:38:17pm
    Author:  Ramon

  ==============================================================================
*/

#include "WDFPreAmp.h"

void WDFPreAmp::prepare(double sampleRate)
{
    c1.prepare(sampleRate);
    c2.prepare(sampleRate);
    c3.prepare(sampleRate);
    c4.prepare(sampleRate);
    c5.prepare(sampleRate);
}
inline StageVoltages WDFPreAmp::processStageU1(double sample)
{
    vs.setVoltage(sample);
	vs.incident(i1.reflected());
    StageVoltages voltages;
	voltages.grid = wdft::voltage<double>(s1);
	voltages.cathode = wdft::voltage<double>(p1);
    i1.incident(vs.reflected());

    return voltages;
}
inline StageVoltages WDFPreAmp::processStageU2(double sample)
{
    vs2.setVoltage(sample);
    vs2.incident(i2.reflected());
	StageVoltages voltages;
	voltages.grid = wdft::voltage<double>(s3);
	voltages.cathode = wdft::voltage<double>(p2);
    i2.incident(vs2.reflected());
    return voltages ;
}
inline double WDFPreAmp::processPreOut(double sample)
{
	vs3.setVoltage(sample);
	vs3.incident(i3.reflected());
	i3.incident(vs3.reflected());

	return wdft::voltage<double>(s6);
}
inline double WDFPreAmp::process(double sample)
{
	auto u1 = processStageU1(sample);
    double u1Grid = u1.grid;
	double u1Cathode = u1.cathode;

	double u1Plate; //= NN(u1Grid - u1Cathode); 

	auto u2 = processStageU2(u1Plate);
	double u2Grid = u2.grid;
	double u2Cathode = u2.cathode;

	double u2Plate; //= NN(u2Grid - u2Cathode);

	return processPreOut(u2Plate);
	
}