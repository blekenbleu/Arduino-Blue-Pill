*evolved from*:&nbsp; <font size=+2><b> 
[stm32duino PWM_FullConfiguration](https://github.com/stm32duino/STM32Examples/tree/main/examples/Peripherals/HardwareTimer/PWM_FullConfiguration)  </b></font>  

*maybe evolving to*:&nbsp; <font size=+2><b> 
[@wotever's Direct Drive harness tensioner](https://github.com/blekenbleu/Direct-Drive-harness-tension-tester)  
and our [SimHubPWMfans](https://github.com/blekenbleu/Arduino-Blue-Pill/tree/main/SimHubPWMfans) </b></font>  

STM is IMO **unjustifiably** proud of [their PWM implementation](https://github.com/stm32duino/STM32Examples/tree/main/examples/Peripherals/HardwareTimer/All-in-one_setPWM)
which does everything in setup() and nothing in loop()
- What good is a PWM that cannot be changed?
- This sketch controls Blue Pill's LED, which is NOT on a PWM pin, by PWM hardware timer interrupt handlers.
- [This web page](https://forum.arduino.cc/t/how-to-change-arduino-stm32-pwm-frequency-to-20khz-in-arduino-ide/675557) describes Arduino command sequence to change STM32 PWM frequency.   
 
This sketch is a path to *usable* [Blue Pill](https://blekenbleu.github.io/Arduino/) hardware PWM for e.g. [tension testing](https://github.com/blekenbleu/Direct-Drive-harness-tension-tester) or
<a href="https://github.com/blekenbleu/Arduino-Blue-Pill/blob/main/SimHubPWMfans/">fans</a>.

[Fake8](https://github.com/blekenbleu/Fake8) employs an [8-bit multi-byte protocol](https://github.com/blekenbleu/Arduino-Blue-Pill/blob/main/8-bit.md), with 3msb of the first byte for command type;  
PWM wants 16 bits (command type b'111') for period and 7 bits (command type b'100') for PWM %

### Debounced [DCD WRC Shifter](https://blekenbleu.github.io/pedals/#DCD) switches
Debounced switches will be asynchronously reported back to [Fake8 SimHub plugin](https://github.com/blekenbleu/Fake8),  
which also must be modified to handle them...

Minimal latency debounce wants a state machine, based on a loop count and most recently reported switch value:
- Loop count == 0 means no debounce in progress
   - first transition will be reported, then count loops until debounce timeout:  
      - for this switch, loop count should consume &gt; 2 ms:
   ![](https://www.circuitbasics.com/wp-content/uploads/2020/06/Oscilloscope-Bouncing-610x418.png)  
   - Mechanical switch bounce is problematic (only) on closure;  shifter switches are normally open.  
- Switch closure with count 0 sets logical "1", gets immediately reported and provokes non-zero countdown loop
   - Switch values during loop count > 0 are ignored while count gets decremented.
- Switch open with count 0 requires no debounce, gets immediately reported and continue.

### [STM32 API for accessing multiple GPIO pins in parallel](https://github.com/stm32duino/Arduino_Core_STM32/issues/1005)
- STM32 pins are bit-mapped to so-called ports, which *may* be `GPIOA->IDR` and `GPIOB->IDR`.  
- [Arduino_Core_STM32/cores/arduino/pins_arduino.h](https://github.com/stm32duino/Arduino_Core_STM32/blob/a9fdc93fc8b2d5739f0d2100d81a83789dd0bbd0/cores/arduino/pins_arduino.h#L293-L318)  
   `port = digitalPinToPort(pin);`  
   `register = portInputRegister(port);`  
   `uint32_t reg = LL_GPIO_ReadInputPort(port);` // [Description of STM32F1 HAL and low-layer drivers](https://www.st.com/resource/en/user_manual/dm00154093-description-of-stm32f1-hal-and-lowlayer-drivers-stmicroelectronics.pdf)  
    
  - Select 2 pins on the same port, then grab the port word and test those 2 bits simultaneously.  
  - They should never both be held low simultaneously by WRC shifter microswitches.
  - Any time the masked value is non-zero (active low pins), then invoke a debounce timeout.  
- According to [Arduino_Core_STM32/cores/arduino/stm32/PinNames.h](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/cores/arduino/stm32/PinNames.h),  
  pins `PA_0` to `PA_15` should be on `PortA`, with pins `PB_0` to `PB_15` on `PortB`  
