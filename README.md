## Arduino (*mostly*) Blue Pill sketches
As described in [**Arduino for STM32 Black 'n Blue Pills, ESP32-S[2,3]**](https://blekenbleu.github.io/Arduino/), this is my default folder for STM32 Arduino 1.18.13;  
a separate [*portable*](https://docs.arduino.cc/software/ide-v1/tutorials/PortableIDE) Arduino 1.18.16 installation [handles ESP32](https://github.com/blekenbleu/arduino-esp32).  
This Arduino put STM32 core library in `/c/Users/bleke/AppData/Local/Arduino15/packages/STMicroelectronics/hardware/stm32/2.1.0`
### here
- [**many in libraries/**](libraries/)
- [**STM32Examples**](STM32Examples/) from [stm32duino/STM32Examples](https://github.com/stm32duino/STM32Examples)
- [BeltTensionner](BeltTensionner/) was @Wotever's original SimHUb plugin sketch
- [Blue_Blink](Blue_Blink/) is trivial LED blink sketch for STM32 Blue Pill
- [Board_Identify](Board_Identify/) Identify microcontroller for which code is built
- [Chip_ID](Chip_ID/) [Wemos-D1-ESP8266 ESP.getChipId()](https://www.wemos.cc/verify_products)
- [Joystick](Joystick/) axes and buttons over serial ibus
- [new2char](new2char/) 7-bit, first with sync msb;  12 available bits: 5 address + 7 data
- [PWM_FullConfiguration](PWM_FullConfiguration) from [`STM32Examples/examples/Peripherals/HardwareTimer`](STM32Examples/examples/Peripherals/HardwareTimer/)  
- [SerialEcho](SerialEcho/) ESP8266 D1 UNO R1 
- [ServoBeltTensioner](ServoBeltTensioner/) *5 Jul 2021* hacked from @Wotever's BeltTensionner
- [USBcomposite](USBcomposite/) library for Roger Melbourne\'s STM32F1  
- [WiFi_blink](WiFi_blink/) *10 Jun 2021* based on *now-lost* tutorial

### [elsewhere](https://blekenbleu.github.io/Arduino)
- [blek2char](https://blekenbleu.github.io/Arduino/) *15 Jan 2022 update* by @sierses: real Arduino support
- [Blue2charServo](https://blekenbleu.github.io/Arduino/) multi-character control for SimHub Custom serial devices
- [BlueLUT_Servo](https://blekenbleu.github.io/Arduino/) index servo[] based on 3 bits of ASCII values, with 4 lsb to index LUT
- [BluePWMfan](https://blekenbleu.github.io/Arduino/SimHubPWMfans) index fan[] based on 3 bits of ASCII values, with 4 lsb to set PWM duty cycle
- [Blue_ASCII sketch](https://blekenbleu.github.io/Arduino/) for STM32 Blue Pill echoes received characters with hex option.
- [Blue_ASCII_Servo](https://blekenbleu.github.io/Arduino/) sketch for STM32 Blue Pill moves hobby servos based on received ASCII.
- [Blue_Servo](https://blekenbleu.github.io/Arduino/) is trivial hobby servo sketch for STM32 Blue Pill
- [SimHubPWMfans](https://blekenbleu.github.io/Arduino/SimHubPWMfans) index fan[] pair based on lsb of ASCII values, with 6 msb to set PWM duty cycle
