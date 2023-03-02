## 2-byte control for SimHub Custom serial devices

.. for use with [Fake8](https://github.com/blekenbleu/Fake8) 8-bit serial plugin for e.g. 
 SimHub **PWM** [Direct Drive sim harness tension tester](https://github.com/blekenbleu/Direct-Drive-harness-tension-tester)

SimHub Custom Serial protocol loosely inspired by MIDI

### 2 Mar 2023 using [Arduino](https://reference.arduino.cc/reference/en/libraries/stm32_pwm/) Library [STM32_PWM](https://github.com/khoih-prog/STM32_PWM)  

Edit near the top of [blek2byte.ino](blek2char.ino) to select the appropriate target:
```
/* Uncomment one microprocessor */
//#define BLUEPILL 1
//#define BLACKPILL 1
#define UNO 1 // Arduino Uno, Nano
//#define LEONARDO 1 // Arduino Leonardo, Micro
//#define PROMICRO 1 // Sparkfun ProMicro
//#define MEGA 1 // Arduino Mega 2560 
```

