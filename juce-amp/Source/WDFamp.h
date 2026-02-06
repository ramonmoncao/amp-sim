/*
  ==============================================================================

    WDFamp.h
    Created: 5 Feb 2026 9:38:17pm
    Author:  Ramon

  ==============================================================================
*/

#pragma once
#include <chowdsp_wdf/chowdsp_wdf.h>

namespace wdft = chowdsp::wdft;

struct StageVoltages {
	double grid;
	double cathode;
};

class WDFamp 
{
public:
    void prepare(double sampleRate);
	inline StageVoltages processStageU1(double sample);
	inline StageVoltages processStageU2(double sample);

private:

    //U1 stage
	wdft::ResistiveVoltageSourceT<double> vs;  // Input voltage source
    wdft::ResistorT<double> r6{ 68.0e3 }; //68K resistor
	wdft::WDFSeriesT<double, decltype(vs), decltype(r6)> s0{ vs, r6 }; // Voltage source and R6 in series
    wdft::ResistorT<double> r7{ 1.0e6 }; //1Meg resistor
	wdft::WDFSeriesT<double, decltype(s0), decltype(r7)> s1{ s0, r7 }; // R6 and R7 in parallel
	wdft::ResistorT<double> r1{ 1.0e3 }; //1K resistor
	wdft::CapacitorT<double> c4{ 2.2e-6 }; //2.2uF capacitor
	wdft::WDFParallelT<double, decltype(r1), decltype(c4)> p1{ r1, c4 }; // R1 and C1 in parallel
	wdft::WDFSeriesT<double, decltype(s1), decltype(p1)> s2{ s1, p1 }; // Series connection of s1 and P2

	//U2 stage
	wdft::CapacitorT<double> c1{ 1.0e-9 }; //1nF capacitor
	wdft::ResistorT<double> r3{ 10.0e3 }; //10K resistor
	wdft::WDFSeriesT<double, decltype(c1), decltype(r3)> s3{ c1, r3 }; // C1 and R3 in series
	wdft::CapacitorT<double> c5{ 2.2e-6 }; //2.2uF capacitor
	wdft::ResistorT<double> r8{ 4.7e3 }; //4.7K resistor
	wdft::WDFParallelT<double, decltype(c5), decltype(r8)> p2{ c5, r8 }; // C2 and R4 in parallel
	wdft::WDFSeriesT<double, decltype(s3), decltype(p2)> s4{ s3, p2 }; // Series connection of s3 and P2
	wdft::PolarityInverterT<double, decltype(s4)> i1{ s4 }; // Polarity inverter
	wdft::IdealVoltageSourceT<double, decltype(s4)> vs2{ s4 }; // Output voltage source
	
	
};

