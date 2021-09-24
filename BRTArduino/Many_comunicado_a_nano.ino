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
  Braccio.begin();
}
 
void loop() {
  Wire.beginTransmission(23); // Comunicarse con esclavo #23
  Wire.write('S');
  Wire.endTransmission();
 
  Wire.requestFrom(23, 1);    // Solicitar 1 byte del esclavo #23
 
  byte len = Wire.read();
 
  Wire.requestFrom(23, (int)len);  // Solicitar 'len' byte del esclavo #23
 
  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read();    // receive a byte as character
    Serial.print(c);         // print the character
    if(c=='y'){
      Braccio.ServoMovement(x,0, 45, 180, 0, 45,  40);
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
    else if (c=='n'){
      delay(100);
      Braccio.ServoMovement(x,0, 45, 180, 0, 45,  40);
      delay(500);
      }
  }
 
  delay(500);
}
