While working on the motor controller and experimenting with Pulse-width Modulation (PWM) for motor control (PWM will be explained in Part 2 of TrackTT), I’ve managed to accidentally corrupt the bootloader on the arduino. This article will cover my solution to the problem that has aroused.

## Symptoms of a corrupted bootloader
The most common thing that will clearly indicate a corrupt bootloader would be the erratic behaviour of the Arduino IDE (AVRdude throws up errors after successfully uploading a sketch, AVRdude loses the communication with the Arduino midway, etc.). Other possible symptoms of a corrupt bootloader may be erratic behaviour of the arduino on the circuit, however, if such behaviour occurs, you should check first if everything is wired correctly since most of the time, poor wiring may lead to erratic arduino behaviour.

## How a bootloader can become corrupted
There are multiple reasons why a bootloader on an arduino may become corrupted. Usually, this is not a major worry as a corrupted bootloader is a relatively low occurrence. However, the following actions may increase your chance of corrupting your bootloader:
- Using a damaged USB cable or having a USB cable with a loose connection (~~this was my case~~ EDIT: check the bottom of the article)
- Forcibly flashing the wrong bootloader for the board (e.g. uploading an Arduino Leonardo bootloader to an Arduino Uno)
- Being a total maniac and uploading the code with a second arduino, or a USBasp adapter via the ICSP pins or worse, directly using pins D11, D12 and D13 (I mean you can totally do it, but why not use the built-in USB port if it is functional?)



Whatever your reason may be, and you have ended up with a corrupt bootloader, note that this is not the end of the world, and your arduino may still be saved.

## The ICSP pins
All arduino models feature an ICSP header on the board. This header is the six vertical pins that stick out from the top of the board. You can use these pins to program the ATMega328p chip directly by using another arduino or other AVR programmers such as the USBasp programmer.

![ICSP header on an Arduino Nano](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/ICSP%20Header.jpg?raw=true)
ICSP header on an Arduino Nano

Alternatively, the following pins can be connected together and will mimic the functionality of the ICSP header (useful when female jumper wires are not available):

| **Programming Arduino** | **Target Arduino** |
|:-----------------------:|:------------------:|
|           5V            |         5V         |
|           GND           |        GND         |
|           D10           |       RESET        |
|           D11           |        D11         |
|           D12           |        D12         |
|           D13           |        D13         |

## Flashing the bootloader
Once the two arduinos are connected together (assuming you are using an arduino as an ISP programmer), you must flash the ArduinoISP sketch onto your programming arduino. This sketch can be found in `Files→Examples→11.ArduinoISP→ArduinoISP`. Once this sketch is flashed to your programming arduino, you must carefully proceed with the next few steps. Go to Tools and **MAKE SURE** that the board type matches your target board. Once this is checked, change the programmer setting from `AVRISP mkII` to `Arduino as ISP`. After this, click burn bootloader and wait for the process to finish. After the bootloader is burned, congratulations you have repaired your arduino bootloader. After re-flashing of the bootloader, you should always load up a sample piece of code (the sample blink sketch provided in the Arduino IDE should suffice).

## What to do if the Arduino still does not work
If you have tried re-flashing the bootloader, and the arduino still does not work properly, there is a good chance that the ATMega328P chip has failed. Replacing the chip on an arduino UNO is a relatively simple task as it only involves pulling the chip out and inserting a new one. But replacing the chip on the nano requires micro soldering, and it may be easier to replace the entire board.

## Conclusion
In the end, I have managed to fix the bootloader on my arduino and successfully was able to continue using the same arduino without any major problems. I will upload further progress on the motor controller once PWM control is fully tested for possibility. Till then enjoy your day.

## EDIT: Another possibility for failure
Upon further investigation, there is a possibility that none of the reasons above contributed to a bootloader failure. When doing further investigation, it was found that sending a PWM signal into the H-Bridge divider caused feedback to the other pin of arduino, which possibly caused a glitch with the ATMega328P chip causing it to corrupt its memory.

## Sources referenced for this article
[Arduino Support—Burn the bootloader on UNO, Mega, and classic Nano using another Arduino. ](https://support.arduino.cc/hc/en-us/articles/4841602539164-Burn-the-bootloader-on-UNO-Mega-and-classic-Nano-using-another-Arduino)

[USBasp—USB programmer for Atmel AVR controllers](https://www.fischl.de/usbasp/)
