This article will cover how I have prepared the shell of the robot for printing. I will also cover the issues that arose when I was preparing the robot.


This is a picture of how the final design looked:

![Isometric view of the entire shell](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/Freecad%20Overview.png?raw=true)

And now, I will talk about how I got to this design.
## Conditions decided on in Part 1
For the parts together with my team, we have decided that the following conditions should be met:
- the robot will have dimensions of 130x130x43.33 mm.
- The parts will be glued together instead of printing the body as a single part.

## Step 0: Preparing the environment
For designing the parts, I have decided to use FreeCAD, an open source alternative to Fusion360 and Solidworks. While not as powerful as Solidworks, it runs natively on Linux, so there is no need to mess around with a Windows VM in QEMU/KVM and also does not need a licence (we do technically have a licence provided for solidworks, however, we can only use solidworks through remote desktop, and if anyone tried doing that, they will know the experience is abysmal). In the end, it does not really matter which parametric CAD software is used as long as it can output STL files that are used by PrusaSlicer (my choice of slicer for 3D printing).

### Quick Explanation: What is a Slicer
Slicing software, also known as a slicer, is the main software needed for generating G Code for 3D printers. G Code is a set of instructions that tells how the printer should move the nozzle, so it can print a given part. Normally a 3D printer cannot read a 3D model directly (and maybe for the better) as a 3D model does not contain any information about what layer height should the printer use, should the inside be hollow, etc. By using slicing software, we can convert the model into G Code and also configure the model to our liking by specifying a layer thickness, the pattern of the infill (3D prints are not solid on the inside) or even if a print needs supports, where should the supports be placed. 

## Step 1: Designing the sidewalls and first problems
Firstly, I have decided to design the sidewalls in FreeCAD. First, I started with drawing a right-angled triangle that had the side lengths of 130 mm and 43.3 mm. However, after drawing a mockup of a motor using the sketch tools, I realised that the triangle would be too small to facilitate the motor. I have contacted my team with the issue and suggested increasing the height to 60 mm to facilitate the motors. Luckily, they agreed to increase the size, which allowed me to facilitate the motors.
![Problem with the sidewall](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/Sidewall%20Problem.jpg?raw=true)

In the design of the sidewalls I added an extra wall that was perpendicular to the main walls. This small wall will be used to mount one of the TCRT5000 sensors.
For the design, I also decided to add screw holes to mount the motor using M3 screws that I had around. I added a small shelf to support the motor as well as making it easier to align the sidewalls with the baseplate.

![Holes in the sidewall](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/SideWall%20Holes.png?raw=true)


The final sidewall looked like this:
![Sidewall with dimensions](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/Sidewall-Side-Annotated.png?raw=true)

On the other side, the sidewall was mirrored as it would be identical in design just pointing the other way around.

## Step 2: Designing the baseplate
For this part, I have decided to start with a 130x130 mm square that will be 2 mm thick. I have decided to print two sample pieces, which were 10x100 mm and one piece was 2 mm thick, and the other was 3 mm thick. I have stress tested both pieces to check their rigidity, and both tests showed that there were only slight differences in the pieces and that in the long run the thickness would not matter for the competition, therefore I have decided to proceed with 2 mm thick walls for the robot as it would conserve the filament during printing, therefore reducing the cost and the printing time for the pieces.

### Adding sensor holes
In our design, we have decided to go with four TCRT5000 sensors, one on each corner. For the front, we have decided to use sensors and PCBs that were at a 90-degree angle to each other due to the lack of space between the floor and the top of the robot at the front. For the back sensors, we have decided to use upright sensor PCBs that will be screwed in into their respective holders (more on them later). The front holes will be 10.8x5.8 mm in size and will be placed 13 mm away from the front edge and 3 mm from the sides. The back will only feature slight 10.8 mm cutouts to help in aligning the TCRT5000 sensor with the bottom. 

### Adding the battery holder and second problem
For the battery pack, I have decided to add a small 2 mm thick frame that would keep the battery pack in place. I intended on putting the breadboard onto the battery pack on a small shelf, to allow for easy replacement of the batteries when needed, but with the current design, there was a lack of space for the breadboard above the battery pack. Instead of increasing the size of the robot again, and having to redo the entire sidewalls, I have decided to proceed with a more creative solution that I will talk more about in the RoboSumo Part 3 article. For now, no structural changes were introduced.

I have also added 2 mm frames for the front sensor PCBs that will help in keeping the front sensors aligned in place.

Here is a picture of the final design of the baseplate:
![Baseplate with dimensions](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/Baseplate-Top-Dimensions.png?raw=true)

## Step 3: Designing the top
The top was the easiest part to design. It was a flat 2 mm thick panel that had three holes in the middle to facilitate a frame and wire connections for the HC-SR04 sensor. Here is a picture of the top lid:
![Top Annotated](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/Top-Isometric.png?raw=true)

## Step 4 slicing the files and printing them
For final preparations, I have exported all the parts individually and imported them into the slicer. Unfortunately, my Ender 3 does not have a big enough bed to safely print all 4 parts together, so I had to print them out separately.
![Print is almost ready to print](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/Slicer%20Screenshot.png?raw=true)
This picture shows the sidewalls ready for printing.

In the end, the sidewalls looked like this with the motors attached to them:
![Sidewalls with motors](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/Motors%20on%20Sidewalls.jpg?raw=true)

## Conclusion
Overall, while the parts are printing, I have decided to work on the electronics. In the next article, I will cover my creative solution for the electronics for this robot. Till then enjoy your day.