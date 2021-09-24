#include <Braccio.h>
#include <Servo.h>


Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

int buttonPin1 = 2;
int buttonPin2 = 4;
int x=30;
int buttonState; 
int buttonState1;

void setup() {
  pinMode(buttonPin1, OUTPUT);
  pinMode(buttonPin2, OUTPUT);
  Braccio.begin();
  Serial.begin(9600);
  Serial.print("Inicio");
    // estado base
    Braccio.ServoMovement(30,0, 45, 180, 0, 0,  0);  
    //  Hola
    Braccio.ServoMovement(30,90, 90, 90, 90, 90,  0);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin1);
  buttonState1 = digitalRead(buttonPin2);
  delay(100);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    Serial.print("llego 1");
    delay(1000);
    //Inicio de movimiento
    Braccio.ServoMovement(30,0, 45, 180, 0, 0,  0);
    Braccio.ServoMovement(20,0, 125, 125, 110, 0,  0);   
    Braccio.ServoMovement(20,0, 125, 125, 110, 0,  100);   
    delay(500);
    Braccio.ServoMovement(20,0, 100, 125, 110, 0,  100);
    delay(100);
    Braccio.ServoMovement(20,90, 100, 125, 110, 0,  100);
    delay(100);
    Braccio.ServoMovement(20,90, 125, 125, 110, 0,  100);
    Braccio.ServoMovement(20,90, 125, 125, 110, 0,  0);
    Braccio.ServoMovement(30,90, 45, 180, 0, 0,   0);
    Braccio.ServoMovement(30,90, 45, 180, 0, 0,  100);
  } 
  if (buttonState1 == HIGH) {
    // turn LED off:
    delay(100);
    Serial.print("llego 2");
    // turn LED on:
    
    Braccio.ServoMovement(30,90, 45, 180, 0, 0,   0);
    Braccio.ServoMovement(30,180, 45, 180, 0, 0,  0);
    //Inicio de movimiento 2 180 a 0
    Braccio.ServoMovement(30,180, 45, 180, 0, 0,  90);
    Braccio.ServoMovement(20,180, 125, 125, 110, 0,  0);   
    Braccio.ServoMovement(20,180, 125, 125, 110, 0,  100);   
    delay(500);
    Braccio.ServoMovement(20,180, 80, 125, 110, 0,  100);
    delay(100);
    Braccio.ServoMovement(20,0, 80, 125, 110, 0,  100);
    delay(100);
    Braccio.ServoMovement(20,0, 80, 125, 110, 0,  100);
    Braccio.ServoMovement(20,0, 125, 125, 110, 0,  0);
    Braccio.ServoMovement(30,0, 45, 180, 0, 0,   0);
    Braccio.ServoMovement(30,0, 45, 180, 0, 0,  100);
    // Mov 3 de 180 a 90
    Braccio.ServoMovement(30,90, 45, 180, 0, 0,  100);
    Braccio.ServoMovement(20,90, 125, 125, 110, 0,  0);   
    Braccio.ServoMovement(20,90, 125, 125, 110, 0,  100);   
    delay(500);
    Braccio.ServoMovement(20,90, 80, 125, 110, 0,  100);
    delay(100);
    Braccio.ServoMovement(20,180, 80, 125, 110, 0,  100);
    delay(100);
    Braccio.ServoMovement(20,180, 80, 125, 110, 0,  100);
    delay(500);
    Braccio.ServoMovement(20,180, 125, 125, 110, 0,  0);
    Braccio.ServoMovement(30,180, 45, 180, 0, 0,   0);
    Braccio.ServoMovement(30,90, 45, 180, 0, 0,  0);
    
    
  }
}
