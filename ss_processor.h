//------------------------------------------------------------------------
// Copyright(c) 2023 My Plug-in Company.
//------------------------------------------------------------------------

#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"
#include "params.h"
namespace MyCompanyName {

//------------------------------------------------------------------------
//  SineSynthProcessor
//------------------------------------------------------------------------
class SineSynthProcessor : public Steinberg::Vst::AudioEffect
{
public:
	SineSynthProcessor ();
	~SineSynthProcessor () SMTG_OVERRIDE;

    // Create function
	static Steinberg::FUnknown* createInstance (void* /*context*/) 
	{ 
		return (Steinberg::Vst::IAudioProcessor*)new SineSynthProcessor; 
	}

	//--- ---------------------------------------------------------------------
	// AudioEffect overrides:
	//--- ---------------------------------------------------------------------
	/** Called at first after constructor */
	Steinberg::tresult PLUGIN_API initialize (Steinberg::FUnknown* context) SMTG_OVERRIDE;
	
	/** Called at the end before destructor */
	Steinberg::tresult PLUGIN_API terminate () SMTG_OVERRIDE;
	
	/** Switch the Plug-in on/off */
	Steinberg::tresult PLUGIN_API setActive (Steinberg::TBool state) SMTG_OVERRIDE;

	/** Will be called before any process call */
	Steinberg::tresult PLUGIN_API setupProcessing (Steinberg::Vst::ProcessSetup& newSetup) SMTG_OVERRIDE;
	
	/** Asks if a given sample size is supported see SymbolicSampleSizes. */
	Steinberg::tresult PLUGIN_API canProcessSampleSize (Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;

	/** Here we go...the process call */
	Steinberg::tresult PLUGIN_API process (Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;
		
	/** For persistence */
	Steinberg::tresult PLUGIN_API setState (Steinberg::IBStream* state) SMTG_OVERRIDE;
	Steinberg::tresult PLUGIN_API getState (Steinberg::IBStream* state) SMTG_OVERRIDE;

//------------------------------------------------------------------------
protected:
	float fOsc1 = default_Osc1;
	float fOsc2 = default_Osc2;
	float fOsc3 = default_Osc3;
	float fSlide1 = default_Slide1;
	float fOsc1Phase = 0.f;
	float fOsc2Phase = 0.f;
	float fOsc3Phase = 0.f;
	float fFrequency = 0.f;
	float fVolume = 0.f;
	float fDeltaAngle = 0.f;
	float fPit1 = default_Pit1;
	float fPit2 = default_Pit2;
	float fPit3 = default_Pit3;

};

#define P12 (3.14159265f * 2.f)

//------------------------------------------------------------------------
} // namespace MyCompanyName
