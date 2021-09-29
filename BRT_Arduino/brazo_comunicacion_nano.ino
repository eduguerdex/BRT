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
void setup(){
  Braccio.begin();
}

void loop() {
   prender("y");
   prender("n");
   base.write(0); 
  shoulder.write(45);
  elbow.write(180);
  wrist_rot.write(0);
  wrist_ver.write(45);
  gripper.write(40);
  delay(100);
}

void prender(String b){
  if (b=="y") {
    Braccio.ServoMovement(x,0, 45, 180, 0, 45,  40);
    delay(500);
    Braccio.ServoMovement(x,80, 45, 180, 0, 0,  0);  
    delay(300);
    Braccio.ServoMovement(x,80, 80, 180, 90, 0,  0);  
    delay(300); //giro 300º y distancia de 23 cm
    Braccio.ServoMovement(x,80, 80, 180, 90, 0,  90);  
    delay(300);//cerrar
    Braccio.ServoMovement(x,0, 55, 180, 90, 0,  90);  
    delay(300); // comprimir y voltear
    Braccio.ServoMovement(x,0, 55, 180, 60, 0,  90);  
    delay(10); // abrir
    Braccio.ServoMovement(x,0, 75, 180, 30, 0,  90);  
    delay(10); // abrir
    Braccio.ServoMovement(x,0, 75, 180, 90, 0,  0);  
    delay(300); // abrir
    Braccio.ServoMovement(x,0, 45, 180, 0, 45,  0);
    delay(500);
  }
  else if (b=="n") {
    delay(100);
    Braccio.ServoMovement(30,0, 45, 180, 0, 45,  40);
    delay(500);
  }
}
