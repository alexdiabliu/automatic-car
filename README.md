# Obstacle Avoiding Robot with Return-to-Start Feature

## Project Overview

This Arduino project controls a robot that can avoid obstacles and keep track of its movements. The robot uses two motors for movement and three ultrasonic sensors to detect obstacles in front, left, and right directions. If an obstacle is detected, the robot takes a turn to avoid it. Additionally, it logs each move, allowing it to retrace its steps back to the starting position.

## Hardware Requirements

1. **Arduino Uno**
2. **L293D Motor Driver** - To control the motors.
3. **2 DC Motors** (DG01D Dagu robot motors recommended) - For movement and turning.
4. **3 HC-SR04 Ultrasonic Sensors** - For obstacle detection in three directions (front, left, and right).
5. **Jumper Wires and Power Supply** for connections and powering the components.

## Pin Configuration

### Motors
- **Left Motor**  
  - Direction A: Pin `2`
  - Direction B: Pin `3`
  - PWM (Speed Control): Pin `5`
  
- **Right Motor**
  - Direction A: Pin `4`
  - Direction B: Pin `7`
  - PWM (Speed Control): Pin `6`

### Ultrasonic Sensors
- **Front Sensor**
  - Trig Pin: `11`
  - Echo Pin: `12`
  
- **Left Sensor**
  - Trig Pin: `A0`
  - Echo Pin: `A1`
  
- **Right Sensor**
  - Trig Pin: `A2`
  - Echo Pin: `A3`

## Code Functionality

### Setup (`setup()`)
- Initializes serial communication and sets up motor and sensor pins as inputs or outputs.

### Main Loop (`loop()`)
- Continuously checks the distances from each sensor.
- If an obstacle is detected within 20 cm of any sensor:
  - Stops the robot.
  - Turns right or left based on the obstacle’s location.
  - Records each movement to allow the robot to return to the starting point.
- If no obstacles are detected, the robot moves forward, logging each forward move.

### Movement Functions
- **moveForward()**: Moves both motors forward with controlled speed.
- **stopMotors()**: Stops both motors.
- **turnLeft()**: Turns the robot left by moving one motor forward and the other backward.
- **turnRight()**: Turns the robot right by moving one motor backward and the other forward.

### Return to Start (`returnToStart()`)
- Rotates the robot 180 degrees to face the starting direction.
- Executes the stored movements in reverse order to return the robot to its initial position.
