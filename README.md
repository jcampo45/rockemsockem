# Rockem Sockem Source Code

### Project
This is a part of a senior capstone project for Columbia University Mechanical engineering students:  
- Joe Campo
- James Harrison
- Nikiander Pelari
- Elon Gordon

We created a human-motion teleoperated version of the classic game Rockem Sockem Robots. Our implementation included tip-tilt and punch control through harvested human motion.

### Implementation  

Motion was detected using IMUs connected to bracelets and a headband on the operator. Point scoring was enabled by chest-plate embedded buttons and a head-mounted joystick. Tip-tilt enacted by a 2-axis servo gimbal and punch action operated by solenoids attached to four-bar linkages. All parts 3D printed and able to be easily replaced, all processing routed through beaglebone black. Score tracked by 7-segment display, and loser's head pops up at the end of the game, just as in the original.

Interfaces (including both robots):
- 6 chest buttons
- 2 2-axis head joysticks
- 4 sternum servos
- 4 punching solenoids
- 2 head popping solenoids
- 1 5-digit 7-segment display