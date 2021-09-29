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
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin1);
  buttonState1 = digitalRead(buttonPin2);
  base.write(0); 
  shoulder.write(45);
  elbow.write(180);
  wrist_rot.write(0);
  wrist_ver.write(45);
  gripper.write(40);
  delay(100);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
  Serial.print("llego 1");
    // turn LED on:
  Braccio.ServoMovement(x,0, 45, 180, 0, 45,  90);
    delay(500);
  
  Braccio.ServoMovement(x,90, 45, 180, 0, 0,  0);  
    delay(300);
  Braccio.ServoMovement(x,90, 80, 180, 90, 0,  0);  
    delay(300); //giro 300º y distancia de 23 cm
  Braccio.ServoMovement(x,90, 80, 180, 90, 0,  90);  
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
  if (buttonState1 == HIGH) {
    // turn LED off:
    delay(100);
    Serial.print("llego 2");
    // turn LED on:
    Braccio.ServoMovement(x,0, 45, 180, 0, 45,  80);
      delay(200);
    Braccio.ServoMovement(x,0, 120, 180, 0, 0,  80);
      delay(100);
    Braccio.ServoMovement(x,0, 120, 180, 0, 0,  0);
      delay(100);
    Braccio.ServoMovement(x,0, 45, 180, 0, 0,  0);
      delay(100);
    Braccio.ServoMovement(x,0, 45, 180, 0, 0,  80);
      delay(100);
    Braccio.ServoMovement(x,180, 45, 180, 0, 0,  0);  
      delay(100);
    Braccio.ServoMovement(x,180, 80, 180, 90, 0,  0);  
      delay(100); //giro 300º y distancia de 23 cm
    Braccio.ServoMovement(x,180, 80, 180, 90, 0,  80);  
      delay(100);//cerrar
    Braccio.ServoMovement(x,90, 55, 180, 90, 0,  80);  
      delay(100); // comprimir y voltear
    Braccio.ServoMovement(x,90, 55, 180, 60, 0,  80);  
      delay(100); // abrir
    Braccio.ServoMovement(x,90, 75, 180, 30, 0,  80);  
      delay(100); // abrir
    Braccio.ServoMovement(x,90, 75, 180, 90, 0,  0);  
      delay(100); // abrir
    Braccio.ServoMovement(x,90, 45, 180, 0, 0,  0);
      delay(100);
    Braccio.ServoMovement(x,90, 45, 180, 0, 0,  0);  
      delay(100);
    Braccio.ServoMovement(x,90, 80, 180, 90, 0,  0);  
      delay(100); //giro 300º y distancia de 23 cm
    Braccio.ServoMovement(x,90, 80, 180, 90, 0,  40);  
      delay(100);//cerrar
    Braccio.ServoMovement(x,0, 55, 180, 90, 0,  40);  
      delay(100); // comprimir y voltear
    Braccio.ServoMovement(x,0, 55, 180, 60, 0,  40);  
      delay(100); // abrir
    Braccio.ServoMovement(x,0, 75, 180, 30, 0,  40);  
      delay(100); // abrir
    Braccio.ServoMovement(x,0, 75, 180, 90, 0,  0);  
      delay(100); // abrir
    Braccio.ServoMovement(x,0, 45, 180, 0, 45,  0);
      delay(500);
  }
}
