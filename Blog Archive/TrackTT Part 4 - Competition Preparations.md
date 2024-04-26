In this article, I will show all the steps I took prior to the competition day, including the robot design and how I managed to get a compliant robot to work for the competition.

## Summary: What do I currently have
Up to this point, I have tested all the components that will be used (the SN754410NE, the TCRT5000, the arduino nano and the motors), but now I will need to put all the components together and test them with the final code for the competition.

## Mounting the TCRT5000
In general, two methods of mounting the TCRT5000 were provided to us, a custom-built PCB, and a screw-in terminal block. Both methods would work for track TT; however, I have favoured using the PCB for the following reasons:
### Smaller footprint
The PCB took up less space than the terminal block, which allowed me to experiment with the sensor placement easily.
### Easier to mount
The PCB had a large hole that could be used to place a screw inside. Since the hole was large and elongated in one direction, it would facilitate changing the sensor height during the competition. This would not be possible with a permanently mounted solution.
### Less prone to shorts
The components on the PCB sat flush with the pcb, something not entirely possible with a terminal block. Loose components can short with themselves, which had a potential of destroying the sensor.

![PCB vs Terminal Block](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/Sensor+Motor%20Breadboard.jpg?raw=true)

## Designing the electronics
For the electronics, a simple circuit connecting the sensors to the arduino and the SN754410NE is required. I have included a schematic of the circuit below:
![Final TT Schematic](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/TrackTT%20Circuit%20Schematic.png?raw=true)

In this circuit, two sensors and two motors are present. Each motor has its individual sensor that will be connected in a cross-pattern (in other words, the right sensor goes with the left motor, and the left sensor with the right motor). The arduino will be in charge of deciding which motors should be on and off depending on the input received from the IR sensors.

## Writing the code
In previous articles, I have written test code that will now be adapted for TrackTT. Since most of the code is already written, I only need to duplicate it for the second motor. So I have done it like this:
```c++
/*
* TrackTT Controller Code
* Author: Tomasz J. Huczek
* This code is licensed under the MIT licence, please see LICENSE.txt for more information.
*/

const int sensorLeft = 0; // give the left sensor a human-readable name other than A0
const int sensorRight = 1; // give the right sensor a human-readable name other than A1
void setup() {
    /* declare pins
     * 2 and 3 control the Left Motor
     * 4 and 5 control the Right Motor
     */
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);

}

/*
 * Motor Direction functions
 * 1 = forward
 * -1 = backward
 * any other value = stop
 * both functions are identical but control different motors
 */

// Left Motor Drive Function
void motorLeft(int direction) {
    switch(direction) {
        case -1:
            digitalWrite(2, HIGH);
            digitalWrite(3, LOW);
        break;
        case 1:
            digitalWrite(2, LOW);
            digitalWrite(3, HIGH);
        break;
        default:
            digitalWrite(2, LOW);
            digitalWrite(3, LOW);
    }
}

// Right Motor Drive Function
void motorRight(int direction) {
    switch(direction) {
        case -1:
            digitalWrite(4, HIGH);
            digitalWrite(5, LOW);
        break;
        case 1:
            digitalWrite(4, LOW);
            digitalWrite(5, HIGH);
        break;
        default:
            digitalWrite(4, LOW);
            digitalWrite(5, LOW);
    }
}
// Main
void loop() {
    // Checks if the right sensor reads a value above 384 and turns the motor on if true and off if false
    if (analogRead(sensorRight) > 384) motorLeft(1);
    else motorLeft(0);
    // Checks if the right sensor reads a value above 384 and turns the motor on if true and off if false
    if (analogRead(sensorLeft) > 384) motorRight(1);
    else motorRight(0);
}
```

The code above consists of two parts. The motor drive functions, `motorLeft()` and `motorRight()`, which their sole job is to tell the SN754410NE, which direction does the given motor need to drive (performed using a switch case) and the `loop()` function, which checks if the sensors have detected a surface beneath them.

### Why 384
After performing some testing with the robot on the track (more on that later in the article), it was decided that 512 was not sensitive enough, and the robot would drive off track easily. Another value of 256 was tested, and with this value, the robot was too sensitive. Since 256 + 128 = 384, a value of 384 was chosen, mainly to keep the number be a multiple of 8 (in reality, this would not affect the behaviour by a huge amount, however, it was mostly a personal choice for the value).

## TrackTT Considerations
For the TrackTT robot, the following restrictions were given:
- The total mass of the robot may not exceed 500 grams.
- All points of ground contact must fit in a circle of 120 millimeters in diameter.
- The power can only be supplied by 4 AA batteries in the provided battery.
- Maximum budget for extra components is €70.

With these restrictions in mind, I have decided to proceed with the design of the robot.

## Assembly of the robot
The material of choice for the robot was cardboard and hot glue. I decided to go with materials because they were easy to obtain, and the robot did not need to be sturdy for TrackTT. Cardboard is also light and cheap. By sourcing old boxes from recycling, I have decided to build a simple body:

![TT Robot](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/TT%20Robot.jpg?raw=true)

I have decided to stick the breadboard under the battery pack, which may not have been the best idea due to the high centre of gravity, however, by putting the battery pack in an accessible place, I have facilitated for an easy way to replace the batteries in the robot. In my opinion, having easier to replace batteries allows me to quickly change batteries after every stint. In the picture above, you may have also noticed that the centre shaft of the body is curved in the middle. Originally the shaft was longer; however, after on-track testing, the robot responded too early, which caused it to fall off the track easily. By shortening the shaft, the sensors were placed closer to the body, which allowed the robot to decide if it should turn a bit slower. This part was mainly trial and error, but I believe I have got the distance to be reasonable, so the robot would not drive itself off but would still respond rather quickly to the turns on the track.

## At home testing with a paper track
Before testing on the proper track in the lab, I have decided to use the sample track fragments [provided in the RoboSumo cookbook](https://robosumo.eu/cookbook/view.php?mdfile=20231011_145214.md) and printed them out on A3 sheets of paper. With this test, I was able to figure out that a sensitivity of 512 was not enough for the paper track, so I have dropped it to 384 as stated earlier in the post. Here I have provided a video of the test track in action.

<iframe width="560" height="315" src="https://www.youtube.com/embed/YAfI6J45XZA?si=IQsDXMQdkbC6zwvj" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

## The slope test
To do a test for the advanced track, I have decided to take an old, square plastic bucket that I had and attached a track sample to it. With this test, I was able to see that the original design had a flaw where the robot would tip over due to the high center of gravity. Stealing an idea used on wheelchairs, I have decided to add extra skids at the back of the robot to prevent it from tipping over. Under normal operation, the skids would be lifted above the track to avoid adding friction, however, if the robot was about to tip over when going up a slope, the skids would make contact with the ramp, which will allow the robot to continue to drive and let it complete the ramp. This decision will be crucial for the advanced track.

![Underside TT](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/TT%20Robot%20Underside.jpg?raw=true)

### Changing the center of gravity
During the slope test, I have considered moving the battery pack forward. However, after moving the battery pack forward, the front sensors would have made contact with the ground, which would make the robot non-compliant. In the end, I kept the design with the skids as it has worked on a slippery test track quite well during testing.

## Conclusion
Overall, the following conditions were met:
- [x] The total mass of the robot may not exceed 500 grams.
- [x] All points of ground contact must fit in a circle of 120 millimeters in diameter.
- [x] The power can only be supplied by 4 AA batteries in the provided battery.
- [x] Maximum budget for extra components is €70.

This resulted in a compliant robot that was ready for the competition. I have high hopes for this robot as I believe from these tests it will compete well in the competition. However, up until the competition day, I may never be fully sure how the robot will perform on the track, so I will find that out on the first stint. Till then enjoy your day.