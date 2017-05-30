# ProjectATOM

LED.rar is an android studio project for the above mentioned app.

ProjectATOM.ino has the arduino code.

This robot uses a modification of A* algorithm to find the shortest path to the goal as it detects obstacles and updates the square grid and finds the next shortest path considering the obstacles that were detected on it's path.
Build/use a wheeled robot and use an arduino paired with a bluetooth module.
Set the pins of the anduino as shown in the arduino code.

Feel free to modify the arduino code, but the folloing should be done:
Commands from android to arduino:

  f - Move forward

  b - Move backward
  
  l - Turn left
  
  r - Turn right
  
  mf<3 digit step value> - Three digit value of the number of steps to be moved forward
  
  mb<3 digit step value> - Three digit value of the number of steps to be moved behind
  
  ml<5 digit movement time> - Five digit value of the time in milliseconds that the robot should move left
  
  mr<5 digit movement time> - Five digit value of the time in milliseconds that the robot should move right
  
  
  
Commands from arduino to android:

  o<number of steps 'cnt'># //Must be sent when an obstacle is detected. The steps moved 'cnt' should be 0 when the command is first received
  
  r#      //Must be sent when move forward,mb (mf,mb) commands are sent to arduino and the said number of steps is reached, to signal completion.
  
  a#      //The robot moves back the number of steps it moved, to the initial position, when an obstacle is detected when 'mf' command is sent. When the robot has completed the backward movement, a# has to be sent to android, to signal completion.
      
The obstacle setting is completly your choice. You can use the 2 ultrasonic,ir sensors as in the code or add any other type of sensor.
By default, it uses ir sensor between the wheel for tracking movement.

The communication between the android phone and arduino is done using the above commands.
  

In the path find activity of the app, set the distance to the goal in cm.
Boundary value in the maximum space that the robot can use to do the path finding process. Minimum must be 2.
Value * distance is the configuration space grid square's diagonal length.
Place the phone on the robot and set the front direction of the robot towards the goal, and press set angle.


Use the calibrate button in the app to calibrate the turning time of the robot.

Modify the following values in the settings of the app to fit your robot:


* wheelRadius //Radius of the wheels in cm

* numOfSteps  //Number of steps to finish a full rotation

* girdLength  //Grid length for a single grid. This must be the length of the robot

Working of the robot:- 
Email me at rishiswethan.c.r@gmail.com for any querys.
