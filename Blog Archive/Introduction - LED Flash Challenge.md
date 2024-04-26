In week 1 of the RoboSumo design project, we have been tasked with making an LED flash. A simple task, right? To make the task more interesting and challenging, we were asked to make two LEDs flash a binary sequence to transmit a message to a testing computer.

## First things first, the Arduino
The board we have been given for the project is an Arduino Nano. This Arduino model uses an ATMega328PU-TH, a surface mount equivalent of the ATMega328P-U the Arduino Uno utilizes. 
The main benefits of using an Arduino Nano over a Uno are:
- More compact format allows for the design of the robot to be smaller.
- The Nano can be mounted directly on a breadboard, where the Uno would require the use of jumper wires, or a breakout board.

### OK, but how do I use one?
Programming one is straightforward, plug it in using USB to a computer (unless you have the Rev1 Arduino it will be USB), open a C++ IDE of choice, whether it would be the Arduino IDE, CLion or Eclipse, and write code in C++. An Example of a simple LED on/off flasher would be:
```c++
// Basic Arduino LED flasher
void setup() {
    pinMode(2, OUTPUT); // Use pin D2 as an output
}

void loop() {
    digitalWrite(2, HIGH); // Turn LED on
    delay(1e3); // Wait 1 second
    digitalWrite(2, LOW); // Turn LED off
    delay(1e3); // Wait 1 second
}
```
### The above code explained
All the code you write will always have two sections. The `setup()` section and the `loop()` section. In the `setup()` section, you declare what the given pins will be used for. The `pinMode(2, OUTPUT)`, tells the arduino that pin D2 will be used to output a signal. The pinMode function follows the following syntax: `pinMode(pin_number, "INPUT/OUTPUT")`. Note that C++ is a case-sensitive language so functions `pinmode()` or `PINMODE()` will not work and will return an exception.
The second most important function is the `loop()` function. This section is the equivalent of `main()` function found in C++. In this section, your main code will be put in. The most important function with the arduino is the `digitalWrite()` function. This function tells the arduino to set a given pin to 5 or 0 volts. This function uses the following syntax `digitalWrite(pin_number, "LOW/HIGH")`. The pin_number is the number of the pin that you want to output from. The HIGH constant sets the voltage of the pin to 5 volts, and the LOW constant sets the voltage to 0 volts.

## Wiring the Arduino
![Pinout of Arduino](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/Arduino%20Pinout.png?raw=true)
The arduino nano contains 30 pins (as shown in the diagram above). Each pin has a label associated with it. The following table explains what the pins do:

|                   **Pin Name**                   |                                                                                                                                        **Purpose of the pin**                                                                                                                                        |                                    **Example Use**                                     |
|:------------------------------------------------:|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:|:--------------------------------------------------------------------------------------:|
|                        5V                        |                                                                               This is the output pin of the arduino. It provides regulated 5V to external components. It can also be used as an unregulated input pin.                                                                               |                    Powering external components such as transistors                    |
|                       GND                        |                                                                                                This is the common ground pins. It is used to provide a ground (or a 0V line) for external components.                                                                                                |                        Supplying ground to external components                         |
|                       VIN                        |                                            This is the regulated power input pin. It allows external voltage sources to power the arduino. Unlike the 5V pin, this pin is connected to a 5V regulator so any voltage from 5 to 12V gets regulated to 5V.                                             |                        Powering the arduino with a battery pack                        |
|                      D2-D19                      | These are the digital input/output pins. These are used to interface the arduino with other electrical components. In INPUT mode, the pins will sense a voltage between 0 and 5V and return a true/false statement to the MCU. Note that some pins have extra symbols which will be explained below. | INPUT mode: Connecting a switch into the arduino <br/> OUTPUT mode: Controlling an LED |
|                  ~D3,~D5, etc.                   |                                                                                      These are digital input/output pins that support a Pulse-Width Modulation (PWM) output. PWM allows for a variable voltage.                                                                                      |                          Controlling the brightness of an LED                          |
|                      A0-A7                       |                                                     These are the analog input pins. These pins are connected to the 10-bit Analog to Digital converter (ADC) built into the ATMega328p MCU. They will read a voltage usually between 0 and 5V.                                                      |                                Reading a potentiometer                                 |
|                    PC6/RESET                     |                                                                                              This pin allows the arduino to be rebooted using an external button instead of the button on the arduino.                                                                                               |                      Resetting the arduino if it freezes/crashes                       |
|                      TX/RX                       |                                                                       These are the Transmit/Receive pins. These should normally not be used but can be used to send messages over serial connections (normally done via USB).                                                                       |                                   Not commonly used                                    |
| CIPO/COPI/SCK (sometimes known as MOSI/MISO/SCK) |                       These pins are used for SPI communication. SPI allows to connect external modules into the arduino that communicate with the arduino. These pins can also be used to program external microcontrollers (when the arduino is used as an ISP programmer).                        |                 Flashing arduino sketches directly onto an ATMega328p                  |

For the example code above, the pin D2 will be connected to an LED that is connected to the GND pin. When the code runs, the LED should turn on and off with a 1-second interval.

## The LED Flash Challenge
For this challenge, each team was given a number between 1 and 255 to transmit using two LEDs. The following conditions were given for the challenge:
- Before transmitting the sequence, 0s must be transmitted for 5 seconds.
- The starting bit in a sequence is always a 1
- A bit lasts 500 milliseconds
- At the end of the sequence, a 0 must-be transmitted
- After transmitting the initial binary sequence, a sequence of 255-\[the number assigned\] must be transmitted immediately.

### My approach to this challenge
The First thing that may come to mind is using the brute force method to do this challenge. A sample of a brute force code would look like this:
```c++
// Brute force code
void setup() {
    pinMode(2, OUTPUT); // 0 Pin
    pinMode(3, OUTPUT); // 1 Pin
}

void loop() {
    // Transmit a 0
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    delay(500);
    // Transmit a 1
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH));
    delay(500);
    // 1
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH));
    delay(500);
    // 0
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    delay(500);
    
    /* 
     * and so on repeating each segment for each digit
     */
    }
```
This method has several flaws, the main ones being is that it is clunky, ugly, hard to modify and uses a lot of memory. Memory optimization, while it is not important for this challenge, it may become a major problem down the line with more complicated code.

The next version looked like this:
```c++
void setup() {
    pinMode(2, OUTPUT); // 0 Pin
    pinMode(3, OUTPUT); // 1 Pin
}

void flash_led(int digit) {
    if (digit == 1) {
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        delay(500);
        digitalWrite(3,LOW);
    } else if (digit == 0) {
        digitalWrite(3, LOW);
        digitalWrite(2, HIGH);
        delay(500);
        digitalWrite(2,LOW);
    }
}

void loop() {
    flash_led(1);
    flash_led(0);
    flash_led(0);
    // and so on
}
```
This is marginally better as it makes the code look slightly cleaner, but it can still be improved.


### The final code
My final code looked like this [(GitHub raw file)](https://raw.githubusercontent.com/tomaszjhuczek/TUD-RoboSumo-Archive/main/Program%20Files/Week%201-LED%20Flash%20Challenge/LED%20Flash%20Challenge.ino):
```c++
/*
 * LED Flash Challenge Code
 * Author: Tomasz J. Huczek
 * This code is licensed under the MIT Licence, please see LICENCE.txt for information.
 * Note 1: 1 segment = 500 milliseconds.
*/

// Setup arduino pins
 void setup() {
    pinMode(2, OUTPUT); // 0 LED
    pinMode(3, OUTPUT); // 1 LED

}

// Check the argument digit and transmit with the correct LED
void flash_led(int digit) {
    if (digit == 1) {
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        delay(500);
        digitalWrite(3,LOW);
    } else if (digit == 0) {
        digitalWrite(3, LOW);
        digitalWrite(2, HIGH);
        delay(500);
        digitalWrite(2,LOW);
    }
}

// Read an array of numbers and send each digit to the flash_led function.
void transmit(int sequence[8]) {
    flash_led(1); //Start sequence
    for (int x=0;x<8;x++) {
        flash_led sequence[x]); // Read digit x of the sequence
    }
    flash_led(0); //End sequence
}


// Main
void loop() {
    int code[8] = {1,1,0,1,1,0,0,0}; // 27 in binary (already written backwards for the validator)
    int inverted_code[8] = {0,0,1,0,0,1,1,1}; // 228 or inverted 27 in binary
    for (int x=0;x<10;x++) {
        flash_led(0); // Send 0 for 10 segments
    }
    transmit(code); // transmit code
    transmit(inverted_code); // transmit inverted_code

}
```

This code is divided into four main sections, the `setup()`, the `flash_led()` function, the `transmit()` function and the `loop()`. The setup function assigns pins D2 and D3 as output pins. The `flash_led` and `transmit` functions are the main brains of this code. The flash_led function takes in an integer and checks if the given integer is either a 0 or a 1. If it is either of these numbers, it will transmit the assigned sequence to the given digit. The transmit function reads an array that stores the sequence of numbers that will be transmitted and sends each entry in the array one by one into the transmit_led function. The transmit function also sends the start bit, and the end bit before and after transmitting the sequence. Finally, the loop function stores the array with the team ID number in binary as an array and its inverse and then transmits them in order. 

The main benefits of using this code over the "brute force" code are:
- Scalability: The number of sequences sent can be increased without adding too many lines of code.
- Ease of editing: the sequence code can easily be changed by editing a single array instead of the entire code.
- Ease of interpretation: The code is cleaner and therefore easier to read and understand.

Here is a video of the flasher in action:

<iframe width="560" height="315" src="https://www.youtube.com/embed/H2fN2xi0S8I?si=jTSpOPEEL3vTvqCu" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

And here is the result on the validator:
![Result of the LED Flash Challenge: Success!!](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/LED%20Flash%20Challenge%20Screenshot.png?raw=true)

## Conclusion
Overall, while the LED challenge is a straightforward task, I still believe it can show the skill of the engineer performing the task. In the next article I will cover motors and how to control them with an arduino. Till then enjoy your day.