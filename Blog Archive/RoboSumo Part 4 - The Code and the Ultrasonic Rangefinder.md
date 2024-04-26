In this article, I will explain the code we have used for the RoboSumo robot. I will also briefly overview the HC-SR04 sensor.

## Our strategy
In our team, we have decided on the following strategy:
- The robot will spin around in a circle trying to look for a target.
- If it detects a target, it will ram straight into the target.
- If it loses the target, then it will spin the other way around.
- If, for some reason (robot reaching the end of the arena/getting pushed off), the IR sensors detect a white surface, the robot will try to get away from the white surface.

With this in mind, after thorough testing, Conor had written the following code with my help:
```c++
// 
// Robo Sumo code to sense and drive at another robot
// Created by Conor Devenish
// Guidance and editing from Tomasz Huczek
// created 10/04/24

int state = 1;


// Give all the motors a nice name
const int LMF = 2;
const int LMR = 3;
const int RMF = 5;
const int RMR = 6;

void setup() 
{
    // Trigger and echo pins for rangefinder
    pinMode(8, OUTPUT); // trigger pin
    pinMode(7, INPUT);  // echo pin
    
    //Setting pins for motors
    pinMode(LMF, OUTPUT);
    pinMode(LMR, OUTPUT); 
    pinMode(RMF, OUTPUT); 
    pinMode(RMR, OUTPUT); 
    
    Serial.begin(9600); // open a serial link to the computer at 9600 bits/s, used for troubleshooting.

}

double pulse() // Measure the distance between the target and our robot (Sample taken from the cookbook)
{
    unsigned long Techo;
    double distance;
    
    // Send trigger pulse from Arduino to HC-SR04
    digitalWrite(8, HIGH);
    delayMicroseconds(20); // 20 us pulse
    digitalWrite(8, LOW);
    
    // Measure the duration of the echo pulse in microseconds
    Techo = pulseIn(7, HIGH);
    
    // Calculate the distance
    distance = (340e-6 * Techo) / 2.0;
    
    // Short delay to allow any echoes to dissipate
    delay(50);
    
    Serial.println(distance);
    
    return distance;
}

boolean readSensors() { // Outputs true if all sensors see black, otherwise it outputs false
    int sensorVoltageLeft = analogRead(0); 
    int sensorVoltageRight = analogRead(1);
    int sensorVoltageLeftB = analogRead(2);
    int sensorVoltageRightB = analogRead(3);
    
    if(sensorVoltageLeft < 700 && sensorVoltageRight < 700 && sensorVoltageLeftB < 700 && sensorVoltageRightB < 700) return true;
    else return false;
} 

// Main
void loop() {
    if (readSensors() == true) {
        double distance = pulse(); 
        if (distance < 0.75) { // If the sensor senses the other bot (distance is less than 0.75 meters)
            digitalWrite(LMF, 1); //drive forward
            digitalWrite(RMF, 1); 
            
            digitalWrite(LMR, 0);
            digitalWrite(RMR, 0);
        } else {   //the sensor does not sense the other bot
            switch(state) {
                // If in state 0, turn right
                case 0:
                    while(distance > 0.75) {
                        distance = pulse();
                        digitalWrite(RMR, 1); //RMB
                        digitalWrite(LMF, 1); //LMF
            
                        digitalWrite(LMR, 0);
                        digitalWrite(RMF, 0);
                        state = 1;
                    }
                break;
                // If in state 1, turn left
                case 1:
                    while(distance > 0.75) {
                        distance = pulse();
                        digitalWrite(LMR, 1);      // LMB
                        digitalWrite(RMF, 1);    // RMF
                        
                        digitalWrite(LMF, 0);
                        digitalWrite(RMR, 0);
                        state = 0;
                    }
                break;
            }
        }
    } else {
        // If any of the IR reflector sensors detect the ground
        int sensorVoltageLeft;
        int sensorVoltageRight;
        int sensorVoltageLeftB;
        int sensorVoltageRightB;
        
        // Code to move when bot senses it is off the table
        // Created by JR Diesta
        // Modified by Conor Devenish
        
        // Reads the input from all 4 sensors
        sensorVoltageLeft = analogRead(0); 
        sensorVoltageRight = analogRead(1);
        sensorVoltageLeftB = analogRead(2);
        sensorVoltageRightB = analogRead(3);
        
        // Depending on the combination of sensors that detect white, move the robot accordingly.
        if ((sensorVoltageLeft > 512) && (sensorVoltageLeftB < 512) && (sensorVoltageRightB < 512) && (sensorVoltageRight < 512))
        {
            // If only the front-left sensor detects white, turn clockwise away from the edge.
            digitalWrite( LMR, LOW);
            digitalWrite( RMF, LOW);
            
            digitalWrite( LMF, HIGH);
            digitalWrite( RMR, HIGH);
            delay(500);
        }
        if ((sensorVoltageRight > 512) && (sensorVoltageLeftB < 512) && (sensorVoltageLeft < 512) && (sensorVoltageRightB < 512))
        {
            // If only the front-right sensor detects white, turn counterclockwise away from the edge.
            digitalWrite( LMR, HIGH);
            digitalWrite( RMF, HIGH);
            
            digitalWrite( LMF, LOW);
            digitalWrite( RMR, LOW);
            delay(500);
        }
        if ((sensorVoltageLeftB > 512) && (sensorVoltageRightB < 512) && (sensorVoltageLeft < 512) && (sensorVoltageRight < 512))
        {
            // If only the back-left sensor detects white, turn counterclockwise away from the edge.
            digitalWrite( LMR, HIGH);
            digitalWrite( RMF, HIGH);
            
            digitalWrite( LMF, LOW);
            digitalWrite( RMR, LOW);
            delay(500);
        }
        if ((sensorVoltageRightB > 512) && (sensorVoltageLeftB < 512) && (sensorVoltageLeft < 512) && (sensorVoltageRight < 512)) 
        {
            // If only the back-right sensor detects white, turn clockwise away from the edge.
            digitalWrite( LMR, LOW);
            digitalWrite( RMF, LOW);
            
            digitalWrite( LMF, HIGH);
            digitalWrite( RMR, HIGH);
            delay(500);
        }
        if ((sensorVoltageRight > 512) && (sensorVoltageLeft >512))
        {
            // If both the front-left and front-right sensors detect white, go backwards for 2 seconds.
            digitalWrite( LMR, HIGH);
            digitalWrite( RMF, LOW);
            
            digitalWrite( LMF, LOW);
            digitalWrite( RMR, HIGH);
            delay(2000);
        }
        if ((sensorVoltageRightB > 512) && (sensorVoltageLeftB >512))
        {
            // If both the back-left and back-right sensors detect white, go forwards for 2 seconds.
            digitalWrite( LMR, LOW);
            digitalWrite( RMF, HIGH);
    
            digitalWrite( LMF, HIGH);
            digitalWrite( RMR, LOW);
            delay(2000);
        }
    }
}
```
## Explaining the code from my point of view
The code features two possible states for the robot. The "attack" state, and the "defend" state as I call them. When the robot is in the "attack" state, it will actively look for the target using this code:
```c++
double distance = pulse();
if (distance < 0.75) { // If the sensor senses the other bot (distance is less than 0.75 meters)
    digitalWrite(LMF, 1); //drive forward
    digitalWrite(RMF, 1); 
    
    digitalWrite(LMR, 0);
    digitalWrite(RMR, 0);
} else {   //the sensor does not sense the other bot
    switch(state) {
        // If in state 0, turn right
        case 0:
            while(distance > 0.75) {
                distance = pulse();
                digitalWrite(RMR, 1); //RMB
                digitalWrite(LMF, 1); //LMF
    
                digitalWrite(LMR, 0);
                digitalWrite(RMF, 0);
                state = 1;
            }
        break;
        // If in state 1, turn left
        case 1:
            while(distance > 0.75) {
                distance = pulse();
                digitalWrite(LMR, 1);      // LMB
                digitalWrite(RMF, 1);    // RMF
                
                digitalWrite(LMF, 0);
                digitalWrite(RMR, 0);
                state = 0;
            }
        break;
    }
}
}
```
At the beginning of this section, the code features an if statement that checks if the distance measured by the HC-SR04 is less than 0.75 meters. If the statement is true, the robot will go forward. If the distance is above 0.75 meters, then the robot will start searching for the opponent. The direction the robot will spin will be dependent on the direction the robot had spun previously. 

## The HC-SR04 sensor explained
The HC-SR04 is an ultrasonic rangefinder. We have decided to use an ultrasonic rangefinder to work out the distance between our robot and the opponent's robot. The rangefinder uses ultrasonic waves, which bounce from surfaces to calculate the distance the wave traveled by measuring the time it took the wave to reach the receiver after sending a signal from a transmitter located beside the receiver. Using the Techo function provided on the RoboSumo Cookbook, we were able to calculate the distance on the arduino using the rangefinder.
![Image explanation of the HC-SR04](https://www.flyrobo.in/image/cache/wp/lj/blog/ultrasonic-sensor-raspberry-pi/HC-SR04-Timing2-e1504971067156.webp)
This image explains how the HC-SR04 works (Source: www.flyrobo.in)

## "Defence" mode
If one of the four TCRT5000 sensors detects the white ring of the arena, the following code will execute:
```c++
int sensorVoltageLeft;
int sensorVoltageRight;
int sensorVoltageLeftB;
int sensorVoltageRightB;

// Code to move when bot senses it is off the table
// Created by JR Diesta
// Modified by Conor Devenish

// Reads the input from all 4 sensors
sensorVoltageLeft = analogRead(0); 
sensorVoltageRight = analogRead(1);
sensorVoltageLeftB = analogRead(2);
sensorVoltageRightB = analogRead(3);

// Depending on the combination of sensors that detect white, move the robot accordingly.
if ((sensorVoltageLeft > 512) && (sensorVoltageLeftB < 512) && (sensorVoltageRightB < 512) && (sensorVoltageRight < 512))
{
    // If only the front-left sensor detects white, turn clockwise away from the edge.
    digitalWrite( LMR, LOW);
    digitalWrite( RMF, LOW);
    
    digitalWrite( LMF, HIGH);
    digitalWrite( RMR, HIGH);
    delay(500);
}
if ((sensorVoltageRight > 512) && (sensorVoltageLeftB < 512) && (sensorVoltageLeft < 512) && (sensorVoltageRightB < 512))
{
    // If only the front-right sensor detects white, turn counterclockwise away from the edge.
    digitalWrite( LMR, HIGH);
    digitalWrite( RMF, HIGH);
    
    digitalWrite( LMF, LOW);
    digitalWrite( RMR, LOW);
    delay(500);
}
if ((sensorVoltageLeftB > 512) && (sensorVoltageRightB < 512) && (sensorVoltageLeft < 512) && (sensorVoltageRight < 512))
{
    // If only the back-left sensor detects white, turn counterclockwise away from the edge.
    digitalWrite( LMR, HIGH);
    digitalWrite( RMF, HIGH);
    
    digitalWrite( LMF, LOW);
    digitalWrite( RMR, LOW);
    delay(500);
}
if ((sensorVoltageRightB > 512) && (sensorVoltageLeftB < 512) && (sensorVoltageLeft < 512) && (sensorVoltageRight < 512)) 
{
    // If only the back-right sensor detects white, turn clockwise away from the edge.
    digitalWrite( LMR, LOW);
    digitalWrite( RMF, LOW);
    
    digitalWrite( LMF, HIGH);
    digitalWrite( RMR, HIGH);
    delay(500);
}
if ((sensorVoltageRight > 512) && (sensorVoltageLeft >512))
{
    // If both the front-left and front-right sensors detect white, go backwards for 2 seconds.
    digitalWrite( LMR, HIGH);
    digitalWrite( RMF, LOW);
    
    digitalWrite( LMF, LOW);
    digitalWrite( RMR, HIGH);
    delay(2000);
}
if ((sensorVoltageRightB > 512) && (sensorVoltageLeftB >512))
{
    // If both the back-left and back-right sensors detect white, go forwards for 2 seconds.
    digitalWrite( LMR, LOW);
    digitalWrite( RMF, HIGH);

    digitalWrite( LMF, HIGH);
    digitalWrite( RMR, LOW);
    delay(2000);
}
```

The purpose of this code is to protect the robot from driving itself off the arena (whether intentionally or accidentally) or it would allow the robot to attempt to fight back if it was trying to get pushed off the track. If one of the sensors detects white, it will force the program to try to figure out the strategy it should take, depending on which sensor has tripped. If one of the sensors trips, the robot will try to rotate in the opposite direction. However, if two front sensors trip, the robot will reverse for at least two seconds. Likewise, a similar thing will happen if both back sensors trip, but in the opposite direction.

## Conclusion
In the end, the code above was fully functional. Conor and JR put in a really good effort in placing the foundations, and with my suggestions, they were able to build really strong code for the competition. In the next article, I will cover the assembly process. Till then, enjoy your day.