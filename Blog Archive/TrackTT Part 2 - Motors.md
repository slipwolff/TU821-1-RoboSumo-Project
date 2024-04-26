Before building the robot, all components must be tested. The first component I have decided to test was the motors. Motors are the key component for TrackTT along with the TCRT5000 sensor. This article will cover the basics of making a motor move with an arduino.

## Conditions for the test to be successful
- Each motor when connected to a DC source must spin.
- The arduino must be able to move a single motor forward and backward.
- Two motors must move at the same time.

## Texas Instruments SN754410NE
Alongside the arduino, a second IC chip, the [SN754410NE](https://www.ti.com/lit/ds/symlink/sn754410.pdf) was used to assist in driving the motors. This IC is a quadruple H-Bridge divider. Its sole purpose is to drive high-power loads with a separate power source to avoid the arduino from being overloaded and possibly frying itself from over-current. 

![SN754410NE Pinout](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/SN754410NE%20pinout.png?raw=true)
Pinout of the SN754410NE

As visible in the picture above, the chip contains 16 pins. This chip can control two separate motors. Pins A1-A4 are driver inputs, which are used to control the direction of the motor (i.e. is the motor stationary, rotating clockwise or counterclockwise). Pins Y1-Y4 are connected directly to the motors. VCC1 and VCC2 supply the voltage to the motors. GND is the common ground for the motors.

### Why are there four ground pins?
After testing with a multimeter, it was shown that all 4 ground pins are connected together (i.e. shorted). This means a design that has only one ground pin connected is possible. The main reason for having four ground pins is that a heat sink can be connected to the chip. While a heat sink is not required, if one was to be installed, it would ideally have to be grounded. 

### SN754410NE vs BJT Transistors
While BJT transistors such as the [STMicroelectronics TIP122](https://ie.rs-online.com/web/p/darlington-pairs/1031078?gb=s), can control a DC motor, the advantage of using the SN754410NE is that the chip can control a motor bidirectionally. While a bidirectional motor control for TrackTT is not important, it will become important for RoboSumo.

## The DC Motors (and gearboxes)
The DC motors provided were generic DC motors with a gearbox preattached. After performing some research, it was found that the motor resembled [this one](https://ie.rs-online.com/web/p/stem-motion-components/2153179?gb=s) from Kiktronik (it is unknown if this one was exactly used but since these motors are similar, I will use the Kiktronik one as a reference in this and future posts). For this project, the gearbox ratio did not matter as I have not decided to mess with changing the gearbox ratios for TrackTT.

## Testing the Motors
To test the motors, a simple circuit was built as shown in the schematic below:
![Motor Controller Schematic](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/Motor%20Test%20Circuit%20Schematic.png?raw=true)
And this is the circuit built on a breadboard:

![Image of breadboard circuit](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/Motor%20Breadboard.jpg?raw=true)

The circuit consists of the following components:
- A DC Motor
- An Arduino
- The H-Bridge Divider
- Voltage Source
- A 220uF polarised capacitor

In this circuit, the motor was connected to the output of the H-bridge divider, which was controlled by the arduino. 

### What is the 220uF capacitor used for?
The primary use of the capacitor is to stabilise the inrush current caused by the rapid starting/stopping of the motor. By stabilising this current, we can avoid any sudden losses of power into the arduino, which could reset itself if not enough power is provided. 

### Sample Code used for testing motors
To test the motors, a simple program for the arduino was written that would run the motor in one direction for a few seconds, and then in the other direction for another few seconds.

```c++
/*
 * Motor Test Code
 * Author: Tomasz J. Huczek
 * This code is licensed under the MIT Licence, please see LICENCE.txt for information.
*/

void setup() {
    pinMode(3, OUTPUT); // Use D3 as output
    pinMode(4, OUTPUT); // Use D4 as output
}

void driveMotor(int direction) {
  /*
   * 1 = Forward
   * -1 = Backward
   * Anything else = Stop
   */
    if (direction == 1) {
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
    } else if (direction == -1) {
        digitalWrite(4, HIGH);
        digitalWrite(3, LOW);
    } else {
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
    }
}

void loop() {
    driveMotor(1); // Run Forward for 2 seconds
    delay(2e3);
    driveMotor(0); // Stop for 0.5 seconds
    delay(500);
    driveMotor(-1); // Run Backwards for 2 seconds
    delay(2e3);
    driveMotor(0); // Stop for 0.5 seconds
    delay(500);
}
```

<iframe width="560" height="315" src="https://www.youtube.com/embed/KhSp424pVds?si=ytFP55BCK18RsBYa" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe> 

As seen in the video above, the motor is fully working and is able to drive both ways. Both motors were tested and both were working.

## Adding a second motor
After testing both motors, a second one can be added by using the other Y pins on the SN754410NE. When the second motor is added and connected to the arduino in the same way the first motor was connected, the code can be expanded to facilitate a second motor as shown below:

```c++
/*
 * Dual Motor Test Code
 * Author: Tomasz J. Huczek
 * This code is licensed under the MIT Licence, please see LICENCE.txt for information.
*/

void setup() {
    pinMode(3, OUTPUT); // Use D3 as output
    pinMode(4, OUTPUT); // Use D4 as output
    pinMode(5, OUTPUT); // Use D5 as output
    pinMode(6, OUTPUT); // Use D6 as output
}

void driveMotorL(int direction) { // Drive Left Motor
    /*
    * 1 = Forward
    * -1 = Backward
    * Anything else = Stop
    */
    if (direction == 1) {
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
    } else if (direction == -1) {
        digitalWrite(4, HIGH);
        digitalWrite(3, LOW);
    } else {
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
    }
}

void driveMotorR(int direction) { // Drive Right Motor
/*
* 1 = Forward
* -1 = Backward
* Anything else = Stop
*/
    if (direction == 1) {
        digitalWrite(5, HIGH);
        digitalWrite(6, LOW);
    } else if (direction == -1) {
        digitalWrite(5, HIGH);
        digitalWrite(6, LOW);
    } else {
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
    }
}

void loop() {
    driveMotorL(1); // Run Left Motor Forward for 2 seconds
    delay(2e3);
    driveMotorL(0); // Stop Left Motor for 0.5 seconds
    delay(500);
    driveMotorR(1); // Run Right Motor Forward for 2 seconds
    delay(2e3);
    driveMotorR(0); // Stop Right Motor for 0.5 seconds
    delay(500);
    driveMotorL(1);
    driveMotorR(1); // Run Both Motors Forward for 2 seconds
    delay(2e3);
    driveMotorL(0);
    driveMotorR(0); // Stop Both Motors for 0.5 seconds 
    delay(500);
}
```
In this case, the left motor uses pins 3 and 4, and the right motor uses pins 5 and 6.

## Further experiments: Pulse-Width Modulation
Currently the motor has only three states, forwards, backwards and stop. With Pulse-Width Modulation (PWM), a theoretical opportunity of adding finer motor speed control becomes possible. However, upon testing with a simple PWM generator such as the one below, it was quickly shown that this was not the case. 

Sample PWM test:
```c++
/*
 * PWM Test Code
 * Author: Tomasz J. Huczek
 * This code is licensed under the MIT Licence, please see LICENCE.txt for information.
*/
void setup() {
    pinMode(3, OUTPUT); // Use D3 as output
    pinMode(4, OUTPUT); // Use D4 as Output
}

void loop() {
    analogWrite(3, 0); // Stop the motor
    delay(2e3); // wait 2 seconds
    analogWrite(3, 128); // Run the motor at 50% speed (theoretically)
    delay(2e3); // wait 2 seconds
    analogWrite(3, 256); // Run the motor at full speed
    delay(2e3); // wait 2 seconds
}
```

After running this code, the motor did not run correctly, and the H-bridge divider caused feedback to occur to pin 4 which caused the arduino to corrupt its bootloader. The fix for this issue was covered in an earlier article, but after attempting this experiment two times, both with unsatisfactory results, it was scrapped due to a significant risk factor that was not worth the risk.

## Conclusion
With today’s task, it was clear that the arduino was fully able to control the motors. Unfortunately, the PWM experiment was unsuccessful and had to be scrapped. In the next article, I will cover the TCRT5000 sensor, which will be used to detect the track under the robot. Till then enjoy your day. 

## Today's Progress Report:
- [x] Motors tested and running when connected to a DC source.
- [x] Arduino moves a single motor forward and backwards.
- [x] Arduino successfully ran both motors in both directions.
- [ ] Motor PWM was functional (Scrapped idea).