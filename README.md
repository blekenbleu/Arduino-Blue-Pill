## Arduino (*mostly*) Blue Pill sketches
As described in [**Arduino for STM32 Black 'n Blue Pills, ESP32-S[2,3]**](https://blekenbleu.github.io/Arduino/), this is my default folder for STM32 Arduino 1.18.13;  
a separate [*portable*](https://docs.arduino.cc/software/ide-v1/tutorials/PortableIDE) Arduino 1.18.16 installation [handles ESP32](https://github.com/blekenbleu/arduino-esp32).  
This Arduino put STM32 core library in `/c/Users/bleke/AppData/Local/Arduino15/packages/STMicroelectronics/hardware/stm32/2.1.0`
### here
- [**many in libraries/**](libraries/)
- [**STM32Examples**](STM32Examples/) from [stm32duino/STM32Examples](https://github.com/stm32duino/STM32Examples)
- [BeltTensionner](BeltTensionner/) *17 May 2021* @Wotever's original SimHUb plugin sketch
- [blek2char](blek2char/) *15 Jan 2022 update* by @sierses: real Arduino support
- [Blue2charServo](Blue2charServo/) *6 Oct 2021* multi-character control for SimHub Custom serial devices
- [BlueLUT_Servo](BlueLUT_Servo/) *24 Jun 2021* index servo[] based on 3 bits of ASCII values, with 4 lsb to index LUT
- [BluePWMfan](BluePWMfan/) *24 Jun 2021* index fan[] based on 3 bits of ASCII values, with 4 lsb to set PWM duty cycle
- [Blue_ASCII](Blue_ASCII/) *3 Mar 2023* sketch for STM32 Blue Pill echoes received characters with hex option.
- [**Blue_ASCII_Servo**](Blue_ASCII_Servo/) *28 Feb 2023* sketch for STM32 Blue Pill moves hobby servos based on received ASCII.
- [Blue_Blink](Blue_Blink/) *28 Jan 2021* is a trivial LED blink sketch for STM32 Blue Pill
- [Blue_Servo](Blue_Servo/) *21 Apr 2021* is a trivial hobby servo sketch for STM32 Blue Pill
- [Board_Identify](Board_Identify/) *10 Jun 2021* Identify microcontroller for which code is built
- [Joystick](Joystick/) *3 Jan 2019* axes and buttons over serial ibus
- [new2char](new2char/) *28 Oct 2021* 7-bit, first with sync msb;  12 available bits: 5 address + 7 data
- [**PWM_FullConfiguration**](PWM_FullConfiguration) *8 Mar 2023* from [`STM32Examples/examples/Peripherals/HardwareTimer`](STM32Examples/examples/Peripherals/HardwareTimer/)  
- [SerialEcho](SerialEcho/) *10 Jun 2021* ESP8266 D1 UNO R1 
- [ServoBeltTensioner](ServoBeltTensioner/) *5 Jul 2021* hacked from @Wotever's BeltTensionner
- [SimHubPWMfans](SimHubPWMfans/) *30 Sep 2021* index fan[] pair based on lsb of ASCII values, with 6 msb to set PWM duty cycle
- [WiFi_blink](WiFi_blink/) *10 Jun 2021* based on *now-lost* tutorial

### [discussion](https://blekenbleu.github.io/Arduino)
