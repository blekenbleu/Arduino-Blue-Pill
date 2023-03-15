*evolved from*:  
## [PWM_FullConfiguration](https://github.com/stm32duino/STM32Examples/tree/main/examples/Peripherals/HardwareTimer/PWM_FullConfiguration)
STM is IMO **unjustifiably** proud of [their PWM implementation](https://github.com/stm32duino/STM32Examples/tree/main/examples/Peripherals/HardwareTimer/All-in-one_setPWM)
which does everything in setup() and nothing in loop()
- What good is a PWM that cannot be changed?
- This sketch controls Blue Pill's LED, which is NOT on a PWM pin, by PWM hardware timer interrupt handlers.
 
This sketch is a path to *usable* [Blue Pill](https://blekenbleu.github.io/Arduino/) hardware PWM for e.g. [tension testing](https://github.com/blekenbleu/Direct-Drive-harness-tension-tester).

[Fake8](https://github.com/blekenbleu/Fake8) employs an [8-bit multi-byte protocol](https://github.com/blekenbleu/Arduino-Blue-Pill/blob/main/8-bit.md), with 3msb of the first byte for command type;  
PWM wants 16 bits (command type b'111') for period and 7 bits (command type b'100') for PWM %
