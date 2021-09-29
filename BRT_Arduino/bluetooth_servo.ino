#include <SoftwareSerial.h>  // libreria que permite establecer pines digitales
        // para comunicacion serie
#include <Braccio.h>
#include <Servo.h>

SoftwareSerial miBT(7, 8);  // pin 10 como RX, pin 11 como TX

char DATOBT;      // variable para almacenar caracter recibido

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;
int x=30, mot_int=6450;
Servo servo;
String estado;

void setup(){
  Serial.begin(9600);
  miBT.begin(38400);    // comunicacion serie entre Arduino y el modulo a 38400 bps
  
  base.attach(11);
  elbow.attach(10);
  shoulder.attach(9);
  wrist_ver.attach(6);
  wrist_rot.attach(5);
  gripper.attach(3);
  
  base.write(0);
  elbow.write(45);
  shoulder.write(180);
  wrist_ver.write(0);
  wrist_rot.write(0);
  gripper.write(70);
}

void loop(){
  if(miBT.available()>2) // si el caracter recibido es el numero 2
  { 
    delay(100);
    DATOBT = miBT.read();
    String DATO = miBT.readString();
    Serial.println(DATO);
    Serial.println(DATOBT);
    
    if( DATO == "ABR" ){
      delay(30);
      gripper.write(0);
    }
    if( DATO == "CIE" ){
      delay(30);
      gripper.write(70);
    }
    if( DATO == "CWR" ){
      delay(30);
      wrist_rot.write(0);
    }
    if( DATO == "CUWR" ){
      delay(30);
      wrist_rot.write(45);
    }
    if( DATO == "NWR" ){
      delay(30);
      wrist_rot.write(90);
    }
    if( DATO == "CTWR" ){
      delay(30);
      wrist_rot.write(135);
    }
    if( DATO == "UWR" ){
      delay(30);
      wrist_rot.write(180);
    }
    if( DATO == "CWV" ){
      delay(30);
      wrist_ver.write(0);
    }
    if( DATO == "CUWV" ){
      delay(30);
      wrist_ver.write(45);
    }
    if( DATO == "NWV" ){
      delay(30);
      wrist_ver.write(90);
    }
    if( DATO == "CTWV" ){
      delay(30);
      wrist_ver.write(135);
    }
    if( DATO == "UWV" ){
      delay(30);
      wrist_ver.write(180);
    }
    if( DATO == "CSH" ){
      delay(30);
      shoulder.write(30);
    }
    if( DATO == "CUSH" ){
      delay(30);
      shoulder.write(45);
    }
    if( DATO == "NSH" ){
      delay(30);
      shoulder.write(90);
    }
    if( DATO == "CTSH" ){
      delay(30);
      shoulder.write(135);
    }
    if( DATO == "USH" ){
      delay(50);
      shoulder.write(160);
    }
    if( DATO == "CE" ){
      delay(30);
      elbow.write(0);
    }
    if( DATO == "CUTE" ){
      delay(30);
      elbow.write(45);
    }
    if( DATO == "NE" ){
      delay(30);
      elbow.write(90);
    }
    if( DATO == "CTE" ){
      delay(30);
      elbow.write(135);
    }
    if( DATO == "UE" ){
      delay(30);
      elbow.write(180);
    }
    if( DATOBT == 'Z' ){
      delay(30);
      base.write(0);
    }
    if( DATOBT == 'X' ){
      delay(30);
      base.write(15);
    }
    if( DATOBT == 'G' ){
      delay(30);
      base.write(45);
    }
    if( DATOBT == 'H' ){
      delay(30);
      base.write(65);
    }
    if( DATOBT == 'J' ){
      delay(30);
      base.write(90);
    }
    if( DATOBT == 'K' ){
      delay(30);
      base.write(120);
    }
    if( DATOBT == 'Y' ){
      delay(30);
      base.write(180);
    }
    if( DATO == "INICIAL" ){
      delay(30);
      base.write(0);
      elbow.write(45);
      shoulder.write(180);
      wrist_ver.write(0);
      wrist_rot.write(0);
      gripper.write(70);
    }
    else{
      delay(30);  
    }
  }
}
