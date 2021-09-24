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
    //Braccio.ServoMovement(30,90, 90, 90, 90, 90,  0);
}
 
void loop() {
  
  if(digitalRead(7)==HIGH){
      Serial.print("Movimiento activado");
      delay(1000);
      //Inicio de movimiento
      Braccio.ServoMovement(30,0, 45, 180, 0, 0,  0);
      Braccio.ServoMovement(30,0, 90, 180, 90, 0,  0);
      Braccio.ServoMovement(30,0, 90, 180, 90, 0,  70);
      Braccio.ServoMovement(30,90, 45, 180, 90, 0,  70);
      Braccio.ServoMovement(30,120, 45, 180, 120, 0,  70);
      Braccio.ServoMovement(30,120, 45, 180, 125, 110,  70);
      Braccio.ServoMovement(30,120, 45, 180, 120, 0,  70);
      Braccio.ServoMovement(30,90, 45, 180, 90, 0,  70);
      Braccio.ServoMovement(30,0, 90, 180, 90, 0,  70);
      Braccio.ServoMovement(30,0, 90, 180, 90, 0,  0);
      Braccio.ServoMovement(30,0, 45, 180, 0, 0,  0);
    }
    else if(digitalRead(2)==HIGH){{
      delay(100);
      Serial.print("Regresa a inicio");
      
      Braccio.ServoMovement(30,0, 45, 180, 0, 0,  70);
        
      // turn LED on:
      }
  }
  else{
    delay(100);
  }
 
  delay(500);
}
