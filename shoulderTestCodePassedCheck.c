#pragma config(Sensor, dgtl1, shoulderUpButton, sensorTouch)
#pragma config(Sensor, dgtl2, shoulderDownButton, sensorTouch)
#pragma config(Sensor, dgtl3, elbowUpButton, sensorTouch)
#pragma config(Sensor, dgtl4, elbowDownButton, sensorTouch)
#pragma config(Sensor, dgtl7, elbowLimit, sensorTouch)
#pragma config(Sensor, dgtl8, elbowEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl10, shoulderLimit, sensorTouch)
#pragma config(Sensor, dgtl11, shoulderEncoder, sensorQuadEncoder)
#pragma config(Motor, port2, shoulderM, tmotorServoContinuousRotation,
openLoop)
#pragma config(Motor, port3, elbowM, tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard !!*//
//global variables
int sUpperBound = -30;
int sLowerBound = 30;
int eUpperBound = 40;
int eLowerBound = -40;
//TODO remove the waits and add checks for the limit switches
// shoulder positive value is up, negative is down
void shoulderUp(){
motor[shoulderM] = 20;
wait1Msec(1000);
motor[shoulderM] = 0;
}
// moves the shoulder down
void shoulderDown(){

// check if the shoulder has moved too far
if(SensorValue(shoulderLimit) == 1){
motor[shoulderM] = 0;
}else{
motor[shoulderM] = -20;
wait1Msec(1000);
motor[shoulderM] = 0;
}
}
// for elbow negative motor is up, positive is down
void elbowUp(){
motor[elbowM] = -25;
wait1Msec(1000);
motor[elbowM] = 0;
}
void elbowDown(){
if(SensorValue(elbowLimit) == 1){
motor[elbowM] = 0;
}else{
motor[elbowM] = 25;
wait1Msec(1000);
motor[elbowM] = 0;
}
}
// currently we have one gear train and a bicep, one motor and
// shoulder motor positive is up, negative is down.
// integer function that takes the quad encoder location and spits out if the shoulder arm is
within bounds
int sOutOfBounds(int location){
if(SensorValue(shoulderLimit)){
return(2);
}
if(location < sUpperBound){
return(1);
}
if(location > sLowerBound){
return(2);
}
return(0);
}
// integer function that takes th quad encoder location and spits out if the elbow arm is within
bounds
int eOutOfBounds(){
int location = SensorValue(shoulderLimit);
if(location){
return(2);
}
if(location < eUpperBound){
return(1);
}
if(location > eLowerBound){
return(2);

}
return(0);
}
// check the elbow limit
int eLimitCheck(){
return(SensorValue(elbowLimit));
}
// loop to move the shoulder between its extremes
void testLoop(){
int shoulderEVal = SensorValue(shoulderEncoder);
motor[shoulderM] = 20;
while(true){
if(SensorValue(shoulderLimit)){ // not set up yet
motor[shoulderM] = 20;
}
shoulderEVal = SensorValue(shoulderEncoder);
if(sOutOfBounds(shoulderEVal) == 2){
motor[shoulderM] = 20;
}
else if(sOutOfBounds(shoulderEVal) == 1){
motor[shoulderM] = -20;
}
}
}
// elbow test similar to shoulder test, moving the arm between its extremes
void elbowTest(){
//motor[elbowM] = 25;
//wait1Msec(1000);
//motor[elbowM] = 0;
int shoulderEVal = SensorValue(shoulderEncoder);
motor[shoulderM] = 20;
while(true){
if(SensorValue(shoulderLimit)){
motor[elbowM] = 20;
}
shoulderEVal = SensorValue(shoulderEncoder);
if(eOutOfBounds() == 2){
motor[elbowM] = 20;
}
else if(eOutOfBounds() == 1){
motor[elbowM] = -20;
}
}
}
// main loop
task main()
{
// loop to respond to button controls
while(true){

if(SensorValue(shoulderUpButton) == 1){
shoulderUp();
}
if(SensorValue(shoulderDownButton) == 1){
shoulderDown();
}
if(SensorValue(elbowUpButton) == 1){
elbowUp();
}
if(SensorValue(elbowDownButton) == 1){
elbowDown();
}
}
writeDebugStream("%d\n",SensorValue(elbowEncoder));
shoulderUp();
writeDebugStream("%d\n",SensorValue(elbowEncoder));
}
