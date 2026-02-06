/*
  ==============================================================================

    ToneStack.h
    Created: 6 Feb 2026 3:37:38pm
    Author:  Ramon

  ==============================================================================
*/

#pragma once
#include <chowdsp_wdf/chowdsp_wdf.h>

namespace wdft = chowdsp::wdft;
class WDFToneStack
{
public:
	void prepare(double sampleRate);
	inline double process(double sample);
private:

	wdft::ResistorT<double> r17{ 1.0e4 }; //10K resistor
	wdft::CapacitorT<double> c6{ 4.7e-10f }; //470pF capacitor
	wdft::WDFSeriesT<double, decltype(r17), decltype(c6)> s1{ r17, c6 }; // R17 and C6 in series
	wdft::ResistorT<double> r10{ 3.3e4 }; //33K resistor
	wdft::ResistorT<double> r11{ 1.1e5 }; //110K resistor
	wdft::WDFParallelT<double, decltype(r10), decltype(r11)> p1{ r10, r11 }; // R10 and R11 in parallel
	wdft::CapacitorT<double> c7{ 2.2e-8f }; //22nF capacitor
	wdft::CapacitorT<double> c8{ 2.2e-8f }; //22nF capacitor
	wdft::WDFParallelT<double, decltype(c7), decltype(c8)> p2{ c7, c8 }; // C7 and C8 in parallel
	wdft::WDFParallelT<double, decltype(s1), decltype(p2)> p3{ s1, p2 }; // S1 and P2 in parallel
	wdft::WDFSeriesT<double, decltype(p1), decltype(p3)> s2{ p1, p3 }; // Series connection of P1 and P3
	wdft::ResistorT<double> r12{ 1.1e5 }; //110K resistor
	wdft::ResistorT<double> r13{ 1.0e6 }; //1Meg resistor
	wdft::WDFSeriesT<double, decltype(r12), decltype(r13)> s3{ r12, r13 }; // R12 and R13 in series
	wdft::WDFSeriesT<double, decltype(s2), decltype(s3)> s4{ s2, s3 }; // Series connection of S2 and S3
	wdft::ResistorT<double> r14{ 1.25e4 }; //12.5K resistor
	wdft::ResistorT<double> r15{ 1.0e4 }; //10K resistor
	wdft::WDFParallelT<double, decltype(r14), decltype(r15)> p4{ r14, r15 }; // R14 and R15 in parallel
	wdft::WDFSeriesT<double, decltype(s4), decltype(p4)> s5{ s4, p4 }; // S4 and P4 in series
	wdft::ResistorT<double> r16{ 1.0e4 }; //10K resistor
	wdft::WDFSeriesT<double, decltype(s5), decltype(r16)> s6{ s5, r16 };// S5 and R16 in series;
	wdft::PolarityInverterT<double, decltype(s6)> i1{ s6 }; //Polarity inverter
	wdft::IdealVoltageSourceT<double, decltype(s6)> vs{ s6 }; // Input voltage source
};