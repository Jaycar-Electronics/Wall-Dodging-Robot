# Wall Dodging Robot

This clever robot is the perfect way to get started with robotics. The robot explores
its surroundings as it avoids obstacles and walls in its path. Starting with the
provided code, the robot can easily be expanded upon.

This is the updated version, without the rechargable battery - it also has a light sensor on it to stop moving when it gets into dark places such as under beds or tables, and we use the motor shield to save space on the platform.

![hero](images/hero.jpg)

There's a lot more that this little robot can do, check out the [Exploration](#Exploration) section for more ideas once you have finished off the build.

- [Wall Dodging Robot](#Wall-Dodging-Robot)
  - [Bill of Materials](#Bill-of-Materials)
    - [You might also want](#You-might-also-want)
  - [Connection Table](#Connection-Table)
  - [System Overview](#System-Overview)
  - [Assembly](#Assembly)
    - [Assembling the Chassis](#Assembling-the-Chassis)
    - [Soldering the motor controller](#Soldering-the-motor-controller)
    - [Connecting the UNO/Motor controller](#Connecting-the-UNOMotor-controller)
    - [Attaching the sensors](#Attaching-the-sensors)
  - [Programming](#Programming)
    - [Troubleshooting](#Troubleshooting)
  - [Exploration](#Exploration)

## Bill of Materials

| Qty | Code                                     | Description                        |
| --- | ---------------------------------------- | ---------------------------------- |
| 1   | [XC4410](https://jaycar.com.au/p/XC4410) | UNO board                          |
| 1   | [XC4442](https://jaycar.com.au/p/XC4442) | Ultrasonic Sensor                  |
| 1   | [KR3160](https://jaycar.com.au/p/KR3160) | 2 wheeled robotic platform         |
| 1   | [XC4472](https://jaycar.com.au/p/XC4472) | Motor Shield for arduino           |
| 1   | [XC4446](https://jaycar.com.au/p/XC4446) | LDR sensor module                  |
| 1   | [HM3211](https://jaycar.com.au/p/HM3211) | Vertical Header 28pin              |
| 1   | [WC6026](https://jaycar.com.au/p/WC6026) | Socket socket leads 40 pack        |
| 1   | [PH9251](https://jaycar.com.au/p/PH9251) | 9 Volt battery snap to barrel jack |
| 1   | [SB2916](https://jaycar.com.au/p/SB2916) | 9 Volt battery                     |

### You might also want

- Some spare wires, [WH3025](https://jaycar.com.au/p/WH3025) is a good choice as it gives you a number of colours, 2 meters in length.
- Small hot glue gun ([TH1997](https://jaycar.com.au/p/TH1997)) or some extra hot glue ([TH1991](https://jaycar.com.au/p/TH1991))
- Bootlace crimps, for terminals: [PT4433](https://jaycar.com.au/p/PT4433)
- Double-sided tape: [NM2821](https://jaycar.com.au/p/NM2821)
- Extra mounting hardware, such as M3 nuts ([HP0425](https://jaycar.com.au/p/HP0425))

## Connection Table

The motor controller ([XC4472](https://jaycar.com.au/p/XC4472)) fits directly on-top of the uno so you don't have to worry about the pinout of the motor connections. The LDR and ultrasonic sensor ([XC4446](https://jaycar.com.au/p/XC4446) and [XC4442](https://jaycar.com.au/p/XC4442)) connect into the analogue pins on the motor shield, which don't have headers, but we can just solder them in with the [HM3211](https://jaycar.com.au/p/HM3211) vertical headers, as shown later in the assembly section.

| UNO (shield) | Device          |
| ------------ | --------------- |
| A5           | LDR Sensor pin  |
| A4           | Ultrasonic TRIG |
| A3           | Ultrasonic ECHO |

Be sure to connect all of the 5V to the 5V pins, and the GND to GND pins.

## System Overview

![system](images/system.png)

The overall robotic platform is pretty easy to understand. The Ultrasonic detects the distance from the robot to an obstacle, and robot will reverse if needed.

## Assembly

We've broken the assembly instructions into different sections so you can jump around if you need to.

### Assembling the Chassis

In the Robot Chassis kit ([KR3160](https://jaycar.com.au/p/KR3160)) you should find some metal pieces and some long screws, along with the motor gearboxes. Bolt through the motor gearboxes onto the metal mounts as shown below.

![Motors](images/attaching-mount.png)

We'll do this to both sides, so that they are opposing, with the top screw-mounts on opposite sides:

![opposing](images/both-motors.jpg)

You'll find that there's only one real spot where the wheels will actually attach, and you can use the smaller screws to attach the motors to that point.

![positioning motors](images/position.jpg)

The trolley wheel goes near the flat end of the robotic platform, and you can use the broad-headed screws to mount the wheel to the small brass spacers in the kit, like such:

![mounting wheel](images/mounting-wheel.jpg)

Then use the remaining small screws to mount the wheel assembly to the chassis. If you have some spare washers or nuts, you can space them out a bit so that they fit more securely as shown below, or just mount it straight onto the chassis. It shouldn't cause a problem.

![wheel](images/wheel.jpg)

### Soldering the motor controller

The motor controller has plenty of connectors on it, however not all of them have the header pins. You should see 3 rows of 6 solder pads near the analogue connections on the motor controller, this is where we will use some of the [HM3211](https://jaycar.com.au/p/HM3211) pins to solder in.

Break off 3 lots of 4 pins. We are only using 4 as that's what we need, but you can break off longer segments if you want. Place one lot in through the top of the motor shield along the analogue connectors and flip the motor controller around so you can solder underneath as shown below.

![motor controller](images/solder1.jpg)

It might be easier to start with the analogue connections first, then work your way away from the edge; here we've started on the GND row.

![gnd](images/solderheader.jpg)

Tack them in and be sure not to short any of the connections. The connectors are already done on the board, so we don't need to make any new connections here.

![fin solder](images/solder3.jpg)

### Connecting the UNO/Motor controller

Once the motor shield has been soldered and you're happy with it, you can place it on top of the UNO and mount the UNO to the robotic platform. We've found it nicer to mount the uno off to the side a little so that you can still program through the USB-B connector, so we use some double sided tape ([NM2821](https://jaycar.com.au/p/NM2821)) or hot-glue to keep it in place.

![connecting](images/connecting.jpg)

### Attaching the sensors

Next is just the ultrasonic and LDR sensors, which can be placed wherever you wish. Connect the `VCC` and `GND` from each sensor to the `5V` and `GND` on the motor shield, from the header connections that were soldered on previously, then connect the `S`, `TRIG`, and `ECHO` wires to the analogue pins.

![topside](images/top.jpg)

You can do any pin out, but our code sample has LDR on `A5`, `TRIG` on `A4` and `ECHO` on `A3`.

We used hot-glue to fix the sensors in position.

## Programming

The source code is in the `robotCode` folder, which you can modify and upload. Once you've uploaded you should see the robot start driving and turn around if it reaches a wall. It will also stop moving if you turn the lights off, or if it goes underneath a table or bed.

### Troubleshooting

The arduino code has information showing in the serial monitor on `9600` baud. You can prop the motor up on a mug or box so that the wheels are off the ground, and see how it responds to moving your hand in front of the sensor, or covering the LDR with your fingers.

- If the robot does not move to begin with, it might be too dark for the robot already; shine a torch on the LDR of the robot to see if it moves
  - you can calibrate the `light_threshold` in the code to determine at what light level the robot stops moving.
- If the robot keeps hitting a wall, check to see if the robot will hit the wall when facing straight at it.
  - If it hits the wall, then make sure that the `ECHO` and `TRIG` pins are connected the right way, and see what the serial output says.

If the robot hits walls on an angle, it might not detect the wall properly, something similar to below:

![reflection](images/reflect.png)

The only way to combat this is to use two ultrasonic sensors on different angles, so that one of them is going to be a little more perpendicular to the side wall. You can also look in the below [Exploration](#Exploration) section for some ideas, such as using a servo to move the sensor to face the wall.

## Exploration

This is really meant to be a starting platform for robotics, as you can now change the robot in any way that suits; some ideas are below:

- [YM2758](https://jaycar.com.au/p/YM2758) Servo module
  - Attach the servo so that the ultrasonic can sweep across and look at other directions, a bit like the Ultrasonic radar project
- [XC4411](https://jaycar.com.au/p/XC4411) UNO with WiFi
  - Use the Uno with WiFi so that it can accept commands from a computer or phone, similar to our WiFi Rover project.
- [XC4385](https://jaycar.com.au/p/XC4385) Circular RGB LED Lights
  - Circular LEDS makes everything cooler, as it can give impressions on what it's doing or which direction it's travelling. This makes it similar to our [KR9262](https://jaycar.com.au/p/KR9262) robot as well.
- [XC4496](https://jaycar.com.au/p/XC4496) 3 Axis Magnetometer
  - Get a reading of what's north so the robot can find it's way throughout a maze or similar
