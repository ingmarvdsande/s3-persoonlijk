// by Marius Versteegen, 2023

// This application uses the CleanRTOS library.
// CleanRTOS is a collection of wrappers around FreeRTOS.
// It lives in the namespace crt (abbreviation of CleanRTOS).
// It's purpose is to make use of FreeRTOS easier and safer.
//
// To help prevent potential headerfile name clashes, it's constituent files are prefixed with crt_
// The classnames themselves don't need the prefix because of membership of the namespace.
// A benefit of that choice is that you can use autocompletion after typing crt:: to find all CleanRTOS 
// parts.
//

#include <crt_CleanRTOS.h>        // This file includes crt_Config.h  You'll need to change defines there for a release build.
#include <crt_Logger.h>
#include "ClockPin.h"
#include "crt_IRSender.h"
#include "crt_TestSignalPauseDetector.h"
#include "NecReceiver.h"
#include "MessageReceiver.h"
#include "IRSender_Test.h"
#include <crt_Button.h>

namespace crt
{
 	MainInits mainInits;            // Initialize CleanRTOS
	const int pinButtonDump = 23;
	Logger<200> theLogger("Logger", 2 /*priority*/, ARDUINO_RUNNING_CORE, pinButtonDump);
	ClockPin clockPin(2 /*gpio*/, 38000 /*freqHz*/, false /*Invert GPIO*/);  // Define 38kHz clock for gpio pin 2.
	ILogger& logger = theLogger;	// This is the global object. It can be accessed without knowledge of the template parameter of theLogger.

	Handler<10 /*MAXLISTENERCOUNT*/> buttonHandler("ButtonHandler", 2 /*priority*/, ARDUINO_RUNNING_CORE, 100 /*periodMs*/, 3000 /*batchTimeUs*/); // Don't forget to call its start() member during setup().
	Button<1> buttonA ("A" /*name*/, 22 /*pin*/, true/*positive logic*/, buttonHandler);
	
	MessageReceiver messageReceiver("MessageReceiver", 2 /*priority*/, 4000 /*stackBytes*/, ARDUINO_RUNNING_CORE);
	NecReceiver necReceiver("NecReceiver", 2 /*priority*/, 4000 /*stackBytes*/, ARDUINO_RUNNING_CORE, messageReceiver);
	SignalPauseDetector signalPauseDetector("SignalPauseDetector", 2 /*priority*/, 4000 /*stackBytes*/, ARDUINO_RUNNING_CORE, necReceiver); // Don't forget to call its start() memeber during setup().
	IRSender irSender("IRSender", 2 /*priority*/, 4000 /*stackBytes*/, ARDUINO_RUNNING_CORE, clockPin); // Don't forget to call its start() memeber during setup().
	IRSender_Test irSenderTest("IRSenderTest", 2 /*priority*/, 4000 /*stackBytes*/, ARDUINO_RUNNING_CORE, buttonA, irSender); // Don't forget to call its start() member during setup().
	// FlagSetter     flagSetter  ("FlagSetter",   2 /*priority*/, 4000 /*stackBytes*/, ARDUINO_RUNNING_CORE, flagListener);
}
// ********  end of constant part of this .ino file  **************

void setup()
{
	ESP_LOGI("checkpoint", "start of main");vTaskDelay(1);
}

void loop()
{
	vTaskDelay(1);// Nothing to do in loop - all example code runs in the 4 threads above.
}
