### 8-bit USB serial protocol for Arduino, with apologies to [MIDI](https://blekenbleu.github.io/MIDI/)
as used in [**Fake8** SimHub plugin](https://github.com/blekenbleu/Fake8)
and [PWM_FullConfiguration](https://github.com/blekenbleu/Arduino-Blue-Pill/tree/main/PWM_FullConfiguration) Arduino sketch
for e.g. [PWM tension testing](https://github.com/blekenbleu/Direct-Drive-harness-tension-tester)  
```
/*
 ; 4 msb of first byte in command sequences
 ; 1 == msb: command; 2 bytes for 110x and 100x
 ; 110x == 3 msb: 1 command with 12-bit value in 2 bytes
 ; 100x == 3 msb: 32 commands with 7 bits in second byte as value
 ; 111x == 3 msb: 8 commands with 7 bits from second and third byte as 16-bit value  
 ; 101x == 3 msb: 31 commands with second byte as 7-bit count of following 7-bit values.
 ; 1011 1111: reset in 1 byte
 */
```
