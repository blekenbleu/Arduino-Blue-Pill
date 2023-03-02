// ---------------------------------------------------------------------
// ---------------------- SETTINGS SECTION -----------------------------
// ---------------------------------------------------------------------

// GLOBAL SETTINGS : How many steps maximum the stepper can travel
const int totalWorkingRange = 5000;
const int centerPositionPercent = 50;

// STEPPER 1 SETTINGS
const int stepper1_pulsePin = 9; // Must be either 9 or 10
const int stepper1_directionPin = 3;
const int stepper1_enablePin = 2;
const int stepper1_hallSensorPin = A1; // Must be an analog pin
const int stepper1_reverseDirection = true;

// STEPPER 2
#define ENABLE_STEPPER_2;
#if defined(ENABLE_STEPPER_2)
const int stepper2_pulsePin = 10; // Must be either 9 or 10
const int stepper2_directionPin = 5;
const int stepper2_enablePin = 4;
const int stepper2_hallSensorPin = A2; // Must be an analog pin
const int stepper2_reverseDirection = false;
#endif

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

#include "src/FastAccelStepper/FastAccelStepper.h"
#include "src/FastAccelStepper/AVRStepperPins.h"
#include "AxisDriver.h"

FastAccelStepperEngine engine = FastAccelStepperEngine();

AxisDriver axisDriver1 = AxisDriver();
AxisSettings axisSettings1 = AxisSettings(
	1,
	stepper1_hallSensorPin,
	stepper1_pulsePin,
	stepper1_directionPin,
	stepper1_enablePin,
	totalWorkingRange,
	stepper1_reverseDirection,
	centerPositionPercent);

#if defined(ENABLE_STEPPER_2)
AxisDriver axisDriver2 = AxisDriver();
AxisSettings axisSettings2 = AxisSettings(
	2,
	stepper2_hallSensorPin,
	stepper2_pulsePin,
	stepper2_directionPin,
	stepper2_enablePin,
	totalWorkingRange,
	stepper2_reverseDirection,
	centerPositionPercent);
#endif

AxisDriver* axisDrivers[] = {
   &axisDriver1
#if defined(ENABLE_STEPPER_2)
	,&axisDriver2
#endif
};

AxisSettings* axisSettings[] = {
   &axisSettings1
#if defined(ENABLE_STEPPER_2)
	,&axisSettings2
#endif
};

const int axisDriversCount = sizeof(axisDrivers) / sizeof(AxisDriver*);

void setup() {
	Serial.begin(19200);
	Serial.println(String(axisDriversCount) + " steppers enabled");

	engine.init();

	for (int i = 0; i < axisDriversCount; i++) {
		axisDrivers[i]->begin(&engine, axisSettings[i]);
	}
}

void processCommand(String command) {
	bool processed = false;
	for (int i = 0; i < axisDriversCount; i++) {
		if (command.startsWith(axisDrivers[i]->CommandPrefix())) {
			axisDrivers[i]->processCommand(command.substring(3));
			processed = true;
		}
	}

	if (!processed) {
		Serial.println("Unrecognised command");
	}
}

void loop() {
	
	if (Serial.available()) {
		String command = Serial.readStringUntil('\n');
		processCommand(command);
	}

	for (int i = 0; i < axisDriversCount; i++) {
		axisDrivers[i]->loop();
	}
}