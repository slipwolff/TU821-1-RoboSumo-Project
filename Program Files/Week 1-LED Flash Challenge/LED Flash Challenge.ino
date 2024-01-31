/*
 * LED Flash Challenge Code
 * Author: Tomasz J. Huczek
 * This code is licensed under the MIT License, please see LICENSE.txt for information.
 * Note 1: 1 segment = 500 milliseconds
*/

// Setup arduino pins
void setup() {
    pinMode(2, OUTPUT); // 0 LED
    pinMode(3, OUTPUT); // 1 LED

}

// Check argument digit and transmit with the correct LED
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

// Read an array of numbers and send each digit to the flash_led function
void transmit(int sequence[8]) {
    flash_led(1); //Start sequence
    for (int x=0;x<8;x++) {
        flash_led sequence[x]); // Read digit x of sequence
    }
    flash_led(0); //End sequence
}


// Main
void loop() {
    int code[8] = {1,1,0,1,1,0,0,0}; // 27 in binary (already written backwards for validator)
    int inverted_code[8] = {0,0,1,0,0,1,1,1}; // 228 or inverted 27 in binary
    for (int x=0;x<10;x++) {
        flash_led(0); // Send 0 for 10 segments
    }
    transmit(code); // transmit code
    transmit(inverted_code); // transmit inverted_code

}