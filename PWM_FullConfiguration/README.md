## PWM_FullConfiguration
STM is IMO **unjustifiably** proud of [their PWM implementation](https://github.com/stm32duino/STM32Examples/tree/main/examples/Peripherals/HardwareTimer/All-in-one_setPWM)
which does everything in setup() and nothing in loop()
- What good is a PWM that cannot be changed?
- This sketch uses interrupts to control Blue Pill's LED, which is not on a PWM pin.
 
This sketch appears to be a path for *usable* [Blue Pill](https://blekenbleu.github.io/Arduino/) hardware PWM with e.g. [tension testing](https://github.com/blekenbleu/Direct-Drive-harness-tension-tester).