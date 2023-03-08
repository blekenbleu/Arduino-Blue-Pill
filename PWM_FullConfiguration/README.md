*evolved from*:  
## [PWM_FullConfiguration](https://github.com/stm32duino/STM32Examples/tree/main/examples/Peripherals/HardwareTimer/PWM_FullConfiguration)
STM is IMO **unjustifiably** proud of [their PWM implementation](https://github.com/stm32duino/STM32Examples/tree/main/examples/Peripherals/HardwareTimer/All-in-one_setPWM)
which does everything in setup() and nothing in loop()
- What good is a PWM that cannot be changed?
- This sketch uses interrupts to control Blue Pill's LED, which is not on a PWM pin.
 
This sketch appears to be a path for *usable* [Blue Pill](https://blekenbleu.github.io/Arduino/) hardware PWM with e.g. [tension testing](https://github.com/blekenbleu/Direct-Drive-harness-tension-tester).

[Fake8](https://github.com/blekenbleu/Fake8) protocol uses 3msb of the first byte for command type;  
PWM wants 16 bits (command type b'111') for period and 7 bits (command type b'100') for PWM %
