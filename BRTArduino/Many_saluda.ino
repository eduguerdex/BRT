#include <Wire.h>
#include <Braccio.h>
#include <Servo.h>
#define Button1 2
#define Button2 4

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
  pinMode(Button1,INPUT);
  pinMode(Button2,INPUT);
  Braccio.begin();
  Braccio.ServoMovement(x,0, 45, 180, 0, 0,  0);  
}
 
void loop() {
  
  if(digitalRead(Button2)==HIGH){
      Serial.print("Movimiento activado");
      delay(1000);
      //Inicio de movimiento
      Braccio.ServoMovement(20,0, 45, 180, 0, 0,  0);
      Braccio.ServoMovement(20,150, 90, 90, 90, 90,  0); //Robot recto
      Braccio.ServoMovement(x,150, 45, 180, 0, 0,  0); 
      Braccio.ServoMovement(20,150, 45, 180, 90, 0,  0); 
      Braccio.ServoMovement(x,0, 95, 140, 90, 0,  0);
      Braccio.ServoMovement(20,0, 45, 140, 90, 0,  0);
      delay(1000);
      Braccio.ServoMovement(30,0, 45, 180, 0, 0,  0);
    }
    else if(digitalRead(Button1)==HIGH){
      {
      delay(100);
      Serial.print("Regresa a inicio");
      Braccio.ServoMovement(x,0, 45, 180, 0, 0,  70);
      }
  }
  else{
    delay(100);
  }
  delay(500);
}
