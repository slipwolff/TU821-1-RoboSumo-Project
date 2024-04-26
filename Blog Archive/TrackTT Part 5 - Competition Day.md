Today is the big day for TrackTT. This is the last article that will cover TrackTT, and in this article I will cover the events that occurred in the competition.

## Reminder of our contestant
![Trashy, the racing robot](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/TT%20Robot.jpg?raw=true)

In Part 4, I have covered the preparations for this robot. In summary, I have decided to make the robot out of cardboard and scraps. I have also done pre-stint testing at home with a paper track.
The robot had to meet the following conditions to qualify for the competition:
- [x] The total mass of the robot may not exceed 500 grams.
- [x] All points of ground contact must fit in a circle of 120 millimeters in diameter.
- [x] The power can only be supplied by 4 AA batteries in the provided battery.
- [x] Maximum budget for extra components is €70.

Since I have tested the robot before the day, I was able to get the robot early on the track.

## Arriving in the contest hall
Due to having a completed robot, I was able to qualify into the early attempts. All I can say, the queue for the early attempts was huge. Around 50 robots have qualified for an early stint. With the robot ready for the competition, I was able to put the robot on the track and let it complete the stint.

## The basic track
![TrackTT Basic Track](https://robosumo.eu/cookbook/uploads/IMG_20231018_163444.jpg)
Image of the basic track
Source: RoboSumo Cookbook
The first attempt had to be done on the basic track first before being able to qualify for the advanced track. To complete this track, the robot had to do a full loop on the track. Given that I had performed pre-track testing, I was able to successfully complete the basic track.

<iframe width="560" height="315" src="https://www.youtube.com/embed/-9-DXSff778?si=gHz9cb8E-SPH_Vpj" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

Overall, the fastest time I have got on the basic track was 12.32 seconds. This gave me a 12th place out of 92 contestants for the basic track. In my opinion, this puts me in a good position. However, this was not the end of the day yet.

## The advanced track
The advanced track was harder, as the name suggests. The main change from the basic track was that slopes were introduced. In theory, the slopes should not pose much of a challenge. Well, I was wrong about that.

### Sensor placement
While the height of the sensors for the basic track did not matter, it was a massive game changer in the advanced track. Too high, the robot would stop on the track. Too low, it may become non-compliant. Overall, it took me around 9 attempts to complete the advanced track (I don't know how many exactly as I stopped counting after 5, but 9 is a good estimate). 

<iframe width="560" height="315" src="https://www.youtube.com/embed/cZL5CKNVUrw?si=AakagGD-jp8XQOAu" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

To complete the track, I had to change my strategy entirely. I have tried multiple things to try to get it to work:

### Change no.1
First, I have decided that changing the code to add a failsafe that if none of the sensors detect anything, go straight on. Here is a snippet of the code I have included (this was added to the code covered in Part 4)
```c++
// Main
void loop() {
    /*
    OLD CODE:
    // Checks if the right sensor reads a value above 384 and turns the motor on if true and off if false
    if (analogRead(sensorRight) > 384) motorLeft(1);
    else motorLeft(0);
    // Checks if the right sensor reads a value above 384 and turns the motor on if true and off if false
    if (analogRead(sensorLeft) > 384) motorRight(1);
    else motorRight(0);
     */ 
    
    // NEW CODE
    if (analogRead(sensorRight) > 384 && (analogRead(sensorLeft) < 384)) {
        // If the left sensor detects space, stop the right motor
        motorLeft(1);
        motorRight(0);
    } else if (analogRead(sensorRight) < 384 && (analogRead(sensorLeft) > 384)) {
        // If the right sensor detects space, stop the left motor
        motorLeft(0);
        motorRight(1);
    } else {
        // Otherwise run both motors (so both motors above or below 384)
        motorLeft(1);
        motorRight(1);
    }
}
```
Unfortunately, this was not the solution as the robot would roll off the opposite end of the track due to a turn being placed directly after the ramp.

### Change no.2
Given that changing the code did not provide a solution, I reverted to the previous code and decided to change the height of the sensors. This was a success as I was able to complete a stint with the robot. With the stint completed, I have decided that this was the final solution for the advanced track.

I have completed the advanced track in 15.73 seconds, which is not the best time possible, but it has given me a 12th place out of 38 contestants for the advanced track.

For the rest of the competition, I have decided to stay because I was curious how well other contestants have performed. When possible, I tried helping others to complete their stints and also saw some interesting robots along the way.

## After competition afterthoughts
After the competition has finished, I have come up with possible improvements for the design. By looking at other robots, especially the faster ones, I quickly saw that most of them had one thing in common, bigger wheels. In my opinion, this is the easiest way to get a better time on the track as bigger wheels equals a bigger speed (and smaller torque, but changes in torque would be negligible in this competition). 
Another idea that would have improved the TrackTT times would be getting rid of the arduino. The main purpose of the arduino was to control the motors based on the input of the TCRT5000 sensors. By replacing the arduino with a comparator circuit, mass would be reduced and possibly the circuit would be loaded less than it currently was. Another thing that could be replaced would be the SN754410NE IC as the motors for this competition did not need to spin both ways, so two NPN transistors would have been sufficient for motor control.

## Conclusion
Overall, I believe that the competition was a success, and the skills gained in the competition will become useful for the RoboSumo part of the competition. This is the final post for TrackTT, and all future posts will relate to the RoboSumo part of the competition. Till then, enjoy your day.