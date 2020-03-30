# Simple Arduino Scoreboard

Arduino sketch to control a 2-team scoreboard.  

This is a 'toy' I built for my son, but sharing it here as an example of simple Arduino project, for those willing to learn.

It will display 2 digits on a multi-digit 7-segment display, each being the score of the team. Button 1 and 2 increase the value of digits 1 and 2. Button 3 resets both scores to 0.

## Components

* 1x Arduino Leonardo
* 1x 4-digit 7-segment display
* 3x push-buttons
* 1x 9V Battery
* 7x 330 Ohm resistors
* 3x 2.2K resistors
* 2x Mini-Protoboards and jumper cables

## Operation

To make this work, you basically need to know two things: (1) how to display numbers in a 4-digit 7-segment display, and (2) how to set up a button so that you can detect a button-push event from your code:

* The two digits corresponding to the scores are displayed at position 1 and 4 of a 4-digit 7-segment display. Check [this link](https://raspi.tv/2015/how-to-drive-a-7-segment-display-directly-on-raspberry-pi-in-python) to understand how to print digits on multi-digit displays.

* When the corresponding button is pressed, the score increases. Check [this link](https://www.arduino.cc/en/Tutorial/Pushbutton) to understand how to set up a push-button in Arduino and detect when the button has been pressed.

The code you can find in this repository is basically a combination of these 2 ideas, translated to 2 digits and 3 buttons. 

## Schematics

![Schematics of the Arduino scoreboard](https://github.com/joeserr/arduino-scoreboard/blob/master/imgs/skema_bb.png)
