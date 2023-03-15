/*
  PWM full configuration
  This sketch fully configures a PWM by HardwareTimer:  no CPU load.
  Blue Pill LED is not on a PWM pin; generata hardware PWM on another pin
  Instead, interruption callbacks are used to toggle a second pin: `pin2`,
  which for Blue Pill LED is set to PC13.

  Note: verify that PWM 'pin' has HardwareTimer capability for your board
  This is specially true for F1 series (BluePill, ...)
*/

#if !defined(STM32_CORE_VERSION) || (STM32_CORE_VERSION  < 0x01090000)
#error "Due to API change, this sketch is compatible with STM32_CORE_VERSION  >= 0x01090000"
#endif

// 'pin' is driven by PWM hardware, while 'pin2' PWM is controlled through interrupt callbacks
// Blue Pill LED is PC13, not a PWM pin
  #define pin   PB9
  #define pin2  PC13

void Update_IT_callback(void)	// Update event at PWM rising edge in PWM1 mode
{
  digitalWrite(pin2, HIGH);
}

void Compare_IT_callback(void)	// Compare match event corresponds to PWM falling edge in PWM1 mode
{
  digitalWrite(pin2, LOW);		// pin2 will approximate PWM pin
}

// AppData/Local/Arduino15/packages/STMicroelectronics/hardware/stm32/2.4.0/cores/arduino/HardwareTimer.h
HardwareTimer *MyTim;
uint32_t channel;
void setup()
{
	// Configure pin2;  it is not controlled by HardwareTimer
	pinMode(pin2, OUTPUT);

	// Initialize serial and wait for port to open:
	Serial.begin(9600);
	while (!Serial)
		delay(1);           // wait for native USB serial port to connect
	Serial.write("PWM_FullConfiguration: connected! pin2 = "); Serial.println(pin2);

	// Automatically retrieve TIM instance and channel associated to pin
	// This is used for compatibility with all STM32 series.
	TIM_TypeDef *Instance = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(pin), PinMap_PWM);
	channel = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(pin), PinMap_PWM));

	Serial.write("channel "); Serial.print(channel); Serial.write(" for pin "); Serial.println(pin); // 'channel 31 for pin 17'

	// Instantiate HardwareTimer object;  'new' HardwareTimer is not destroyed when setup() ends.
	MyTim = new HardwareTimer(Instance);
	MyTim->setMode(channel, TIMER_OUTPUT_COMPARE_PWM1, pin);
	Serial.write("new HardwareTimer() TIMER_OUTPUT_COMPARE_PWM1 mode set");

	// setOverflow() with MICROSEC_FORMAT or HERTZ_FORMAT computes Prescalerfactor based on getTimerClkFreq()
	// setOverflow() takes uint32_t;  fractional Hz by large MICROSEC_FORMAT;  50 usec = 20kHz
	MyTim->setOverflow(2000000, MICROSEC_FORMAT); // 2000000 microseconds = 2000 milliseconds
	MyTim->setCaptureCompare(channel, 50, PERCENT_COMPARE_FORMAT); // 50%
	MyTim->attachInterrupt(Update_IT_callback);
	MyTim->attachInterrupt(channel, Compare_IT_callback);
	MyTim->resume();
	Serial.write("\nleaving setup()... Prescalerfactor = "); Serial.println(MyTim->getPrescaleFactor());
}

void Reset()
{
	MyTim->pause();
	MyTim->setCaptureCompare(channel, 0, PERCENT_COMPARE_FORMAT);
	MyTim->resume();
	Serial.write("PWM_FullConfiguration:  PWM % = ");  Serial.print(MyTim->getCaptureCompare(channel, PERCENT_COMPARE_FORMAT));
	Serial.write(";  PWM usec = "); Serial.println(MyTim->getOverflow(MICROSEC_FORMAT));
}

/*
 ; 
 ; 1 == msb: command; 2 bytes for 110x and 100x
 ; 100x == 3 msb: 32 commands with 7 bits in second byte as value
 ; 101x == 3 msb: 31 commands with second byte as 7-bit count of following 7-bit values.
 ; 110x == 3 msb: 1 command with 12-bit value in 2 bytes
 ; 111x == 3 msb: 8 commands with 7 bits from second and third byte as 16-bit value  
 ; 1011 1111: reset in 1 byte
 */
byte state[2] = {0,0}, once = 0, command[3] = {0,0,0};
void loop()
{
	// need to receive 1 to 40,000 to set 20kHz to 50Hz: 16 bits in 3 bytes: 111000bb 0bbbbbbb 0bbbbbbb
	byte received;
    bool got = false;

	while (0 < Serial.available()) {
		received = Serial.read();
		Serial.print(received, HEX);
		if (0xBF == received) {
			Reset();
			state[0] = state[1] = 0;
			return;
		}
		else if (0 == state[0] || 0x80 & received) {	// not processing a command or start of one?
			command[0] = received;
			state[1] = 0;
			if (4 > (state[0] = command[0] >> 5)) {
				Serial.write(" expecting a command byte; ignoring received: "); Serial.println(received);
				state[0] = 0;
			}
		}
		else if (5 != state[0]) {
			byte limit = (4 == state[0]) ? 3 : 2;
     		unsigned int value;
     
			if (state[1] < limit) {
				command[state[1]] = received;
				state[1]++;
			}
			else {
				Serial.write(" too many bytes for command "); Serial.print(0xE0 & command[0]);
				Serial.write("; ignoring received = "); Serial.println(received);
                state[0] = state[1] = 0;
				return;
			}
			if (state[1] < limit)
				return;						// need another byte
			switch (state[0]) {
				case 4:						// 7 data bits: PWM percent
					MyTim->setCaptureCompare(channel, command[2], PERCENT_COMPARE_FORMAT);
					break;
				case 6:						// 12-bit 2-byte
					Serial.write(" 12-bit command not yet implemented\n");
					return;
				case 7:						// 3-byte 16-bit command: set PWM period
					value = 3 & command[0];
					value <<=7;
					value |= command[1];
					value <<=7;
					value |= command[2];
					if (0 < value)
						MyTim->setOverflow(50 * value, MICROSEC_FORMAT);	// 50 usec = 20kHz, 2,000,000 = 0.5Hz
					else {
						Serial.write(" setOverflow(0) disallowed\n");
						return;
					}
					break;
				default:
					Serial.write("Unknown state: "); Serial.print(state[0]); Serial.write("; ignoring received = ");
					Serial.println(received);
					return;
			}
			state[0] = state[1] = 0;
		}
		else {								// deal with state 5 long commands
			if (once)
				return;
			Serial.write("long commands not yet implemented\n");
			once++;
			return;
		}
		got = true;
	}
	if (got) {
		Serial.write("\n");
		got = false;
	}
}
