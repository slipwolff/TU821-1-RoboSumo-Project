Welcome to the part 2 of the project. Since TrackTT is now completed, which was an individual effort, we are now moving to working in groups of 3 for this project.

## Meet the team
Together with Conor Devenish [(chosendozer)](https://robosumo.eu/chosendozer/) and JR Diesta [(rustydragon)](https://robosumo.eu/rustydragon/), we have decided to team up together and decided to create ReggieRobot. In our team, the following roles were designated:

| **Person** |                                                                **Role**                                                                |
|:----------:|:--------------------------------------------------------------------------------------------------------------------------------------:|
|   Conor    |                                                  Head of Programming/Code development                                                  |
|     JR     |                                                   Head of Design / CAD and assembly                                                    |
|   Myself   | Head of Electronics, Manufacturing of Parts (including preparing of CAD files for printing and slicing the files), General C++ Advisor |

## Initial Robot Design
For the first week leading up to the RoboSumo competition, we have decided to sit down and work on the design concepts for the robot. This day was primarily used as a day to throw random ideas and take them down. During this day we came up with absurd ideas that could work but would require a lot of effort to make such as a radar sensor, using cameras to track the opponent or even rockets (OK, rockets would not be compliant, but they would be fun). Ultimately, we have settled with doing a wedge design for our robot.

### Wedge design, explained
The main reason for a wedge would be to allow the opponent to go on top of the robot and get stuck on top of our robot, allowing for an easy win by pushing the helpless opponent off the arena. This design would be the simplest to implement and would allow for a stealthy robot. 

## Iteration 1
![Concept 1](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/Concept%201.jpg?raw=true)

The first concept of our robot would have the following features:
- 4 wheels
- 4 motors, 1 for each wheel
- 2 front wheels would be smaller
This concept was scrapped for iteration 2 as having two smaller powered wheels would require a change in gear ratios, and also the battery pack would struggle with powering four motors.

## Iteration 2
![Concept 2](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/Concept%202.jpg?raw=true)

This design removed the front motors, but still was not perfect as the turning radius of the robot would still be hindered due to the front wheels being rigid. So back to the drawing board.

## Iteration 3
![Concept 3](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/Concept%203.jpg?raw=true)

We have decided to make a significant change to the design by removing a wheel and proceeding with a tricycle design. A taildragger design was thought of but was quickly shown to be impractical to implement in practice. This design also would be impractical to implement as there were not enough clearances in the front to feature a full wheel, hence we decided to go back to the blueprints.

## Iteration 4
![Concept 4](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/Concept%204.jpg?raw=true)

This design, in my opinion, was the coolest. Instead of using wheels, we would have introduced tracks, similar to the ones found on diggers. This design would not have problems with turning as the tracks would allow for a full 360-degree turn in a single spot. Unfortunately, this idea had to be scrapped since tracks were hard to source and expensive (it would have been a great design though).

## Iteration 5, the final design

![Concept 5](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/Concept%205.jpeg?raw=true)

This design removes the front wheels entirely in favour of a skid block. This removes the necessity of manufacturing a dedicated front wheel and also allows for decent turns to be made. We have decided to proceed with this design as it would be the easiest to manufacture, and also it would function the best for a RoboSumo robot. With all of this in mind, we could proceed with preparing the parts for printing.

## RoboSumo requirements
Before preparing the parts for printing, the following criteria had to be considered:
- The robot must not weigh more than 500 grams.
- The max size of the robot is 150x150x150 millimeters at the start of the competition. Expansion is allowed after the start. 
- All parts of the robot must be properly secured.
- The robot can only be powered by four AA batteries.

With these conditions in mind, we have decided to go with a robot of the following dimensions: 130 mm in length and width and 43.3 mm in height. For the CAD drawings, I have decided to take the burden of converting the sketches into parts due to understanding how to correctly prepare parts for 3D-printing. Nevertheless, JR did assist in preparing the parts and helped in designing the holder for the HC-SR04 ultrasonic sensor (this sensor will be covered in RoboSumo Part 4). 

## Other ideas
Our design will also feature the use of four TCRT5000 sensors, one on each corner to detect if the robot has left or has been pushed off the arena. On the top of the robot, an ultrasonic rangefinder will be located to help in finding the opponent. The design will also use 70 mm in diameter wheels, which were provided in the RoboSumo kit. 

## Conclusion
Overall, the design is ready for printing, and in the next article I will cover the process of moving a paper design into CAD software and preparing the files for printing, so stay tuned for updates on this blog. Till then, enjoy your day.