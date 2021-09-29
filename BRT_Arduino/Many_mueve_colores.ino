#include <Wire.h>
#include <Braccio.h>
#include <Servo.h>


Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;
int x=30;
void setup() {
  Wire.begin();        // unirse al bus i2c como master
  Serial.begin(9600);  // configurar monitor serie a 9600
  pinMode(7,INPUT);
  pinMode(4,INPUT);
  pinMode(2,INPUT);
  Braccio.begin();
    // estado base
    Braccio.ServoMovement(30,0, 45, 180, 0, 0,  0);  
    //  Hola
    Braccio.ServoMovement(30,90, 90, 90, 90, 90,  0);
}
 
void loop() {
  
  if(digitalRead(7)==HIGH){
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
    else if(digitalRead(2)==HIGH){{
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
  else{
    delay(100);
  }
 
  delay(500);
}
