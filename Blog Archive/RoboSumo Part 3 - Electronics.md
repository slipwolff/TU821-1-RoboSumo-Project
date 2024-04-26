In the last article, you may have noticed that I ran into an issue with the breadboard being too big for the robot. In this article, I will cover my solution for the electronics I came up with.

## Say hello to the perfboard
For the electronics, I have decided to ditch the breadboard in favour of a perfboard. The perfboard requires soldering, which is not ideal when prototyping circuits, however, it will allow for a more rigid design of the circuit as well as a more compact design of the circuit. Using my favourite [part shop](https://ie.rs-online.com/), I ordered the following components:
- An ATMega328P MCU
- 27 pF capacitors
- 16 MHz crystals
- 28 pin sockets
- 16 pin sockets
- 2,3 and 4 pin headers
The plan is to solder these components to a perfboard. The advantage of using this approach is that the completed circuit was 1/3 of the size of a breadboard with all the components, and also there is a smaller risk of components falling out of a perfboard rather than a breadboard since the components are soldered into place. In the design, I have decided to use sockets rather than soldering the IC chips directly to the perfboard to facilitate easy replacement of the chips. It is also easier and cheaper to replace a broken socket rather than a broken chip.

## Goodbye Arduino
As you can see from the component list above, I have decided to buy an ATMega328P MCU. Since the arduino uses the same chip, all arduino sketches should be compatible with the standalone MCU since the Arduino only features an extra USB controller chip, other than that it is just a breakout board for an ATMega328P [as further shown in the following schematic](https://content.arduino.cc/assets/NanoV3.3_sch.pdf). I have decided to go with this MCU to allow for backwards compatability with already written Arduino code as each pin on the ATMega MCU has a corresponding Arduino pin as shown in the diagram below:
![Atmega 328 Pinout](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/raw/main/Blog%20Archive/Resources/ATMega328P%20Pinout.webp)
Source: The Engineering Projects

## The crystals and capacitors explained
The ATMega328P features a built-in 8 MHz oscillator that in practice is not really that useful as it has sloppy tolerances. By using an external oscillator composed of a 16 MHz crystal and two 27 pF capacitors, we can increase the precision of the clock speed in the MCU as well as allow it to operate at a higher speed, which may be crucial for making faster decisions on the arena. Using an external oscillator is also required for the Arduino bootloader, which is needed to run Arduino sketches.

## Final Circuit schematic
The following schematic was drafted up for the design of the main control board:
![Control board schematic](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/RoboSumo%20Control%20Board.png?raw=true)

This schematic was used as a reference when wiring the circuit board.

## Wiring the circuit board

![Breadboard vs Perfboard](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/Perfboard%20vs%20Breadboard.jpg?raw=true)

Soldering the components to the perfboard was the easy part since all components went into their slots and only needed solder. Arranging the wires was a different story. I have decided to use 22 American wire gauge wires for this project, which may have been a mistake. The main problem with 22AWG wires is that they are stiff. This stiffness makes them really hard to work with, and I had issues where the rings on the perfboards would unstick as I was trying to bend the wires into shape. In the end, I have managed to assemble a working circuit for the control board. I have provided a picture of the control board below:
![Finished control board](https://github.com/tomaszjhuczek/TUD-RoboSumo-Archive/blob/main/Blog%20Archive/Resources/Sumo%20Control%20Board.jpg?raw=true)

## Mini board explained
You may be asking yourself what is the small board that is connected via small wires for. This little board will be used to connect the HC-SR04 sensor to the main board. I decided to make a breakout board to facilitate the opening of the top of the robot for maintenance purposes.

I have also placed sockets for the motors, the TCRT5000 senors and the battery pack to avoid soldering these components primarily to simplify the maintenance of these components.

In the design, I have also added a reset button to allow for quick resets to the MCU in case the MCU crashes during operation. This was more of a backup for an unlikely case that may make the robot return to operation in an abnormal situation.

## Conclusion
Overall, the circuit board was a success, and it rescued our robot from another redesign. In my opinion, this is my proudest moment of the entire project as I was able to work with a proper microcontroller and learn how to program one without connecting it directly via USB. It was also a unique design that was not present on other robots and it made our robot stand out compared to other robots. In the next article I will briefly cover the HC-SR04 sensor and talk about the code for our robot. Till then, enjoy your day.