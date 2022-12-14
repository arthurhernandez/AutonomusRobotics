#pragma config(Sensor, in1, light, sensorReflection)
#pragma config(Sensor, dgtl6, rightTouch, sensorTouch)
#pragma config(Sensor, dgtl8, , sensorTouch)
#pragma config(Sensor, dgtl9, leftSwitch, sensorTouch)
#pragma config(Sensor, dgtl10, sonar, sensorSONAR_cm)
#pragma config(Sensor, dgtl12, frontButton, sensorTouch)



//Arthur Hernandez
//Tuesday October 19th
//Autonomous Robotics
#pragma config(Motor, port2, rightMotor, tmotorServoContinuousRotation, openLoop,
driveLeft)
#pragma config(Motor, port3, leftMotor, tmotorServoContinuousRotation, openLoop,
driveRight)
#pragma config(Motor, port5, servoMotor, tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard !!*//
// speed for the motors
int speed = 30;
// distance to stay from the walls
int sonarCutoff = 16;
//reverse backward
void reverse(){
motor[leftMotor] = -speed;
motor[rightMotor] = -speed;
wait1Msec(370);
motor[leftMotor] = 0;
motor[rightMotor] = 0;
}
void turnRight(){
motor[leftMotor] = speed;
motor[rightMotor] = -speed;
wait1Msec(1750); // arbitrary to equate to prior: 2750
motor[leftMotor] = 0;
motor[rightMotor] = 0;
}
//same as turn right but for much less time
void turnRightGentle(){
motor[leftMotor] = speed;
motor[rightMotor] = -speed;
wait1Msec(235); // arbitrary to equate to prior: 2750
motor[leftMotor] = 0;
motor[rightMotor] = 0;
}
void goForward(){
motor[leftMotor] = speed + 2; // 2 to account for the speed disparity and keep it away
from the wall
motor[rightMotor] = speed;
wait1Msec(850);
if(SensorValue(frontButton) == 1){
motor[leftMotor] = 0;
motor[rightMotor] = 0;
turnRight();
}
// leftButton check
if(SensorValue(leftSwitch) == 1){
reverse();
turnRightGentle();
goForward();


}
if(SensorValue(rightTouch)){
reverse();
reverse();
turnRight();
goForward();

}
motor[leftMotor] = 0;
motor[rightMotor] = 0;
if(SensorValue(sonar) <= sonarCuto
ff){

motor[leftMotor] = 0;
motor[rightMotor] = 0; } }
void turnLeft(){
motor[leftMotor] = 13;
motor[rightMotor] = speed;
if(SensorValue(frontButton) == 1){
motor[leftMotor] = 0;
motor[rightMotor] = 0;
turnRight(); }
if(SensorValue(leftSwitch) == 1){
motor[leftMotor] = 0;
motor[rightMotor] = 0;
turnRightGentle();
goForward(); }
if(SensorValue(rightTouch)){
reverse();
reverse();
turnRight();
goForward();

}

}
task main(){
// sonar value
int sv;
while(true){
sv = SensorValue(sonar);
if(sv < 0){
turnLeft();

}

if(sv < sonarCuto
ff){
goForward();
//count = 0;
//else turn left

}
else{
turnLeft();

}
//we hit the bump sensor turn right
if(SensorValue(frontButton) == 1){
// changable
reverse();
turnRight();
}
if(SensorValue(leftSwitch) == 1){
turnRightGentle();
goForward();
}
if(SensorValue(rightTouch)){
reverse();
reverse();
turnRight();
goForward();
}
// try to reallign if possible
sv = SensorValue(sonar);
if(sv < 6){
turnRightGentle();
}
}// end while loop
}
