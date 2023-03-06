### extra libraries for STM32 with Arduino 1.8.13

For information on installing libraries, see: http://www.arduino.cc/en/Guide/Libraries

- [Arduino_CRC32](Arduino_CRC32/)
- [Arduino_DebugUtils](Arduino_DebugUtils/)
- [Board_Identify](Board_Identify/)
- [Servo](Servo/)
- [SimpleTimer](SimpleTimer-master/)
- [STM32_PWM](STM32_PWM/)

STM officially supports [STM32duino](https://github.com/stm32duino) with [core support](https://github.com/stm32duino/Arduino_Core_STM32)
and [**examples**](STM32Examples-main),  
including [All-in-one_setPWM](STM32Examples-main/examples/Peripherals/HardwareTimer/All-in-one_setPWM)
and [PWM_FullConfiguration](STM32Examples-main/examples/Peripherals/HardwareTimer/PWM_FullConfiguration).  

Arduino comes with many libraries, many seemingly AVR-specific, but here are some others:  
**in the Arduino installation folder**:
```
libraries/Adafruit_Circuit_Playground/
libraries/Bridge/
libraries/Esplora/
libraries/Ethernet/
libraries/Firmata/
libraries/GSM/
libraries/Keyboard/
libraries/LiquidCrystal/
libraries/Mouse/
libraries/RobotIRremote/
libraries/Robot_Control/
libraries/Robot_Motor/
libraries/SD/
libraries/Servo/
libraries/SpacebrewYun/
libraries/Stepper/
libraries/Temboo/
libraries/TFT/
libraries/WiFi/
```

### other potentially useful STM32 Arduino libraries
- [STM32_Slow_PWM](https://github.com/khoih-prog/STM32_Slow_PWM)
  drives up to 16 interrupt-driven software PWMs up to 1 kHz from 1 hardware timer
- [Task Scheduler](https://github.com/arkhipenko/TaskScheduler) Cooperative multitasking for Arduino, ESPx, STM32
- [Microcontroller-Id](https://github.com/smartmeio/microcontroller-id-library) retrieve manufacturer's serial number
- [uTimerLib](https://github.com/Naguissa/uTimerLib) Tiny and cross-device compatible timer-driven timed function calls
- [TaskJockey](https://github.com/mbratch/TaskJockey) light-weight, cooperative task manager tracking timed task iterations using millis() in loop()
- [STM32_TimerInterrupt](https://github.com/khoih-prog/STM32_TimerInterrupt)

