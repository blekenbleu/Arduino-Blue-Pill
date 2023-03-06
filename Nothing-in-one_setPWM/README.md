## All or Nothing-in-one_setPWM
STM is IMO **unjustifiably** proud of [their PWM implementation](https://github.com/stm32duino/STM32Examples/tree/main/examples/Peripherals/HardwareTimer/All-in-one_setPWM)
which does everything in setup() and nothing in loop()
- What good is a PWM that cannot be changed?
- Their implementation appears to disable using serial port in loop().

Since serial DOES work with Servo, which invokes some flavor of PWM,  
that appears to be a path for *usable* PWM.
