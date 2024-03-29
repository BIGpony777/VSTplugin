//------------------------------------------------------------------------
// Copyright(c) 2023 My Plug-in Company.
//------------------------------------------------------------------------

#include "ss_controller.h"
#include "ss_cids.h"
#include "vstgui/plugin-bindings/vst3editor.h"

#include "pluginterfaces/base/ibstream.h"
#include "base/source/fstreamer.h"

#include "params.h"

using namespace Steinberg;

namespace MyCompanyName {

//------------------------------------------------------------------------
// SineSynthController Implementation
//------------------------------------------------------------------------
tresult PLUGIN_API SineSynthController::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated

	//---do not forget to call parent ------
	tresult result = EditControllerEx1::initialize (context);
	if (result != kResultOk)
	{
		return result;
	}

	// Here you could register some parameters
	setKnobMode(Vst::kLinearMode);
	parameters.addParameter(STR16("OSC1"), nullptr, 0, default_Osc1, Vst::ParameterInfo::kCanAutomate, kOsc1);
	parameters.addParameter(STR16("OSC2"), nullptr, 0, default_Osc2, Vst::ParameterInfo::kCanAutomate, kOsc2);
	parameters.addParameter(STR16("OSC3"), nullptr, 0, default_Osc3, Vst::ParameterInfo::kCanAutomate, kOsc3);
	parameters.addParameter(STR16("SLIDE1"), nullptr, 0.1, default_Slide1, Vst::ParameterInfo::kCanAutomate, kSlide1);
	parameters.addParameter(STR16("PIT1"), nullptr, 0.1, default_Pit1, Vst::ParameterInfo::kCanAutomate, kPit1);
	parameters.addParameter(STR16("PIT1"), nullptr, 0.1, default_Pit2, Vst::ParameterInfo::kCanAutomate, kPit2);
	parameters.addParameter(STR16("PIT1"), nullptr, 0.1, default_Pit3, Vst::ParameterInfo::kCanAutomate, kPit3);
	
	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API SineSynthController::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!

	//---do not forget to call parent ------
	return EditControllerEx1::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API SineSynthController::setComponentState (IBStream* state)
{
	// Here you get the state of the component (Processor part)
	if (!state)
		return kResultFalse;

	IBStreamer streamer(state, kLittleEndian);

	float fval;
	if (streamer.readFloat(fval) == false)
		return kResultFalse;
	setParamNormalized(kOsc1, fval);
	if (streamer.readFloat(fval) == false)
		return kResultFalse;
	setParamNormalized(kOsc2, fval);
	if (streamer.readFloat(fval) == false)
		return kResultFalse;
	setParamNormalized(kOsc3, fval);
	if (streamer.readFloat(fval) == false)
		return kResultFalse;
	setParamNormalized(kSlide1, fval);
	if (streamer.readFloat(fval) == false)
		return kResultFalse;
	setParamNormalized(kPit1, fval);
	if (streamer.readFloat(fval) == false)
		return kResultFalse;
	setParamNormalized(kPit2, fval);
	if (streamer.readFloat(fval) == false)
		return kResultFalse;
	setParamNormalized(kPit3, fval);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API SineSynthController::setState (IBStream* state)
{
	// Here you get the state of the controller

	return kResultTrue;
}

//------------------------------------------------------------------------
tresult PLUGIN_API SineSynthController::getState (IBStream* state)
{
	// Here you are asked to deliver the state of the controller (if needed)
	// Note: the real state of your plug-in is saved in the processor

	return kResultTrue;
}

//------------------------------------------------------------------------
IPlugView* PLUGIN_API SineSynthController::createView (FIDString name)
{
	// Here the Host wants to open your editor (if you have one)
	if (FIDStringsEqual (name, Vst::ViewType::kEditor))
	{
		// create your editor here and return a IPlugView ptr of it
		auto* view = new VSTGUI::VST3Editor (this, "view", "ss_editor.uidesc");
		return view;
	}
	return nullptr;
}

//------------------------------------------------------------------------
tresult PLUGIN_API SineSynthController::setParamNormalized (Vst::ParamID tag, Vst::ParamValue value)
{
	// called by host to update your parameters
	tresult result = EditControllerEx1::setParamNormalized (tag, value);
	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API SineSynthController::getParamStringByValue (Vst::ParamID tag, Vst::ParamValue valueNormalized, Vst::String128 string)
{
	// called by host to get a string for given normalized value of a specific parameter
	// (without having to set the value!)
	return EditControllerEx1::getParamStringByValue (tag, valueNormalized, string);
}

//------------------------------------------------------------------------
tresult PLUGIN_API SineSynthController::getParamValueByString (Vst::ParamID tag, Vst::TChar* string, Vst::ParamValue& valueNormalized)
{
	// called by host to get a normalized value from a string representation of a specific parameter
	// (without having to set the value!)
	return EditControllerEx1::getParamValueByString (tag, string, valueNormalized);
}

//------------------------------------------------------------------------
} // namespace MyCompanyName
