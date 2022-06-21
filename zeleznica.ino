#include <AccelStepper.h>
#include <ezAnalogKeypad.h>
#include <EEPROM.h>
// Define pin connections

//stepper driver dir and step pin
const int dirPin = 7;
const int stepPin = 6;
//stepper home switch
const int home_switch = 4;
//left and right buttons
const int buttonPin1 = 2;
const int buttonPin2 = 3;
//analog input for the keyboard
ezAnalogKeypad keypad(A0);


//Define variables

//setting positions
//setting servo home
long initial_homing=-1; 

// Define motor interface type
#define motorInterfaceType 1

// Creates an instance
AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);

void setup() {

  //debug
  Serial.begin(9600);
  
  //set keypad
  keypad.setNoPressValue(0); 
  keypad.registerKey(1, 314); 
  keypad.registerKey(2, 410); 
  keypad.registerKey(3, 540);
  keypad.registerKey(4, 232); 
  keypad.registerKey(5, 347); 
  keypad.registerKey(6, 509);
  keypad.registerKey(7, 130);
  keypad.registerKey(8, 274);
  keypad.registerKey(9, 470);
  keypad.registerKey(10, 184);
  

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT); 

  //left and right digital buttons
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);

  //setting home switch
  pinMode(home_switch, INPUT_PULLUP);
  
  delay(20);


  gohome();
}
//resets the stepper home to 0
void gohome(){
  myStepper.setMaxSpeed(200.0);
  myStepper.setSpeed(200.0); 
  myStepper.setAcceleration(200.0); 
  
  while (digitalRead(home_switch)) { 
    myStepper.moveTo(initial_homing);  
    initial_homing--;  
    myStepper.run();  
    delay(5);
  }
  myStepper.setCurrentPosition(0);
  initial_homing=1;
  
  while (!digitalRead(home_switch)) { 
    myStepper.moveTo(initial_homing);  
    myStepper.run();
    initial_homing++;
    delay(5);
  }
  myStepper.setCurrentPosition(0);
  
  myStepper.setMaxSpeed(200.0);
  myStepper.setSpeed(200.0); 
  myStepper.setAcceleration(200.0); 

  Serial.println("home set");
}

//returns the position that the stepper moter needs to move to or 0 if reset home
int buttonPosition(){
  // get analog key value
  int key = keypad.getKey();
  if (key) {
    Serial.println(key);
  }
  delay(10);
  return key;
}

int readIntFromEEPROM(int address){
  return (EEPROM.read(address) << 8) + EEPROM.read(address + 1);
}

void writeIntIntoEEPROM(int address, int number){ 
  byte byte1 = number >> 8;
  byte byte2 = number & 0xFF;
  EEPROM.write(address, byte1);
  EEPROM.write(address + 1, byte2);
}

void writePosition(int writeTo){
  writeIntIntoEEPROM(writeTo*2, myStepper.currentPosition());
  Serial.println(myStepper.currentPosition());
  Serial.println("position set");
}

void moveToPosition(int saveNumber){
  if(!saveNumber)
    return;
  int position = readIntFromEEPROM(saveNumber*2);
  Serial.print("moving to ");
  Serial.println(position);
  if (position>=0)
    myStepper.moveTo(position);
}

void loop() {
  if(digitalRead(buttonPin1) && digitalRead(buttonPin2)){
    Serial.println("Select number to save to");
    digitalWrite(LED_BUILTIN, HIGH);
    int button = buttonPosition();
    while(!button){
      button = buttonPosition();
      if(digitalRead(buttonPin1))
        myStepper.move(1);
        
      else if(digitalRead(buttonPin2))
        myStepper.move(-1);
        
      myStepper.run();
      delay(5);
    }
    writePosition(button);
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  if(digitalRead(buttonPin1)){
    myStepper.move(1);
    delay(10);
  }
    
  if(digitalRead(buttonPin2)){
    myStepper.move(-1);
    delay(10);
  }

  moveToPosition(buttonPosition());
  

  myStepper.run();
  
}
