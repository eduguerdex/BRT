#include <SoftwareSerial.h> // TX RX software library for bluetooth
#include <Braccio.h> // brazo library 
#include <Servo.h> // servo library 
#include <Arduino_SensorKit.h> // sensorkit library 


Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper; // servo nombre

int bluetoothTx = 10; // bluetooth tx en 10 pin
int bluetoothRx = 11; // bluetooth rx en 11 pin

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

String DatoBT;
char boton, StatusBoton ='0';
float tiempoServo =0;


void setup()
{
  // Funciones de inicialización y configuración de la posición inicial para Braccio
   // Todos los servomotores se colocarán en la posición de "seguridad":
   // Base (M1): 90 grados
   // Hombro (M2): 45 grados
   // Codo (M3): 180 grados
   // Muñeca vertical (M4): 180 grados
   // Rotación de muñeca (M5): 90 grados
   // pinza (M6): 10 grados
  //Setup usb serial connection to computer
  Serial.begin(9600);
  Braccio.begin();
  base.write(90); 
  shoulder.write(45);
  elbow.write(180);
  wrist_rot.write(180);
  wrist_ver.write(90);
  gripper.write(10);
  Oled.begin();
  //Setup Bluetooth serial connection to android
  bluetooth.begin(9600);
}

void loop()
{
  //Read from bluetooth and write to usb serial
  Oled.setFont(u8x8_font_amstrad_cpc_extended_r); 
  if(bluetooth.available()>= 2 )
  {
    unsigned int servopos = bluetooth.read();
    unsigned int servopos1 = bluetooth.read();
    unsigned int realservo = (servopos1 *256) + servopos;
    Serial.println(realservo);

    if (realservo >= 1000 && realservo <1180) {
      int servo1 = realservo;
      servo1 = map(servo1, 1000, 1180, 0, 180);
      base.write(servo1);
      Oled.setCursor(0, 0);
      Oled.println("Base ON");
      delay(10);
    }
    if (realservo >= 2000 && realservo <2180) {
      int servo2 = realservo;
      servo2 = map(servo2, 2000, 2180, 0, 180);
      shoulder.write(servo2);
      Oled.setCursor(0, 1);
      Oled.println("Shoulder ON");
      delay(10);
    }
    if (realservo >= 3000 && realservo <3180) {
      int servo3 = realservo;
      servo3 = map(servo3, 3000, 3180, 0, 180);
      elbow.write(servo3);
      Oled.setCursor(0, 2);
      Oled.println("Elbow ON");
      delay(10);
    }
    if (realservo >= 4000 && realservo <4180) {
      int servo4 = realservo;
      servo4 = map(servo4, 4000, 4180, 0, 180);
      wrist_rot.write(servo4);
      Oled.setCursor(0, 3);
      Oled.println("wrist_rot ON");
      delay(10);
    }
    if (realservo >= 5000 && realservo <5180) {
      int servo5 = realservo;
      servo5 = map(servo5, 5000, 5180, 0, 180);
      wrist_ver.write(servo5);
      Oled.setCursor(0, 4);
      Oled.println("wrist_ver ON");
      delay(10);
    }
    if (realservo >= 6000 && realservo <6180) {
      int servo6 = realservo;
      servo6 = map(servo6, 6000, 6180, 0, 180);
      gripper.write(servo6);
      Oled.setCursor(0, 5);
      Oled.println("Griper ON");
      delay(10);
    }
    if (realservo == 0) {
      base.write(90); 
      shoulder.write(45);
      elbow.write(180);
      wrist_rot.write(180);
      wrist_ver.write(90);
      gripper.write(10);
      Oled.setCursor(0, 6);
      Oled.println("Apagado");
      delay(10);
    }
  }
}
