/*
  PWM full configuration
  This example shows how to fully configure a PWM with HardwareTimer.
  Blue Pill LED is not on a PWM pin; generate PWM on another pin
  PWM is generated by hardware: no CPU load.
  In this example both interruption callbacks are used
  to toggle a second pin: `pin2`, which for Blue Pill is set to PC13 for its LED.

  Note: verify that 'pin' for PWM has HardwareTimer capability for your board
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
  digitalWrite(pin2, LOW);		// pin2 will be complementary to pin
}

void Compare_IT_callback(void)	// Compare match event corresponds to PWM falling edge in PWM1 mode
{
  digitalWrite(pin2, HIGH);
}

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
  uint32_t channel = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(pin), PinMap_PWM));

  Serial.write("channel "); Serial.print(channel); Serial.write(" for pin "); Serial.println(pin); // 'channel 31 for pin 17'

  // Instantiate HardwareTimer object;  'new' HardwareTimer is not destroyed when setup() ends.
  HardwareTimer *MyTim = new HardwareTimer(Instance);
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

/*
 ; 
 ; 1 == msb: command; 2 bytes for 110x and 100x
 ; 110x == 3 msb: 1 command with 12-bit value in 2 bytes
 ; 100x == 3 msb: 32 commands with 7 bits in second byte as value
 ; 111x == 3 msb: 8 commands with 7 bits from second and third byte as 16-bit value  
 ; 101x == 3 msb: 31 commands with second byte as 7-bit count of following 7-bit values.
 ; 1011 1111: reset in 1 byte
 */
void loop()
{
	// need to receive 1 to 40,000 to set 20kHz to 50Hz: 16 bits in 3 bytes: 111000bb 0bbbbbbb 0bbbbbbb
}