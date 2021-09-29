#include <SoftwareSerial.h>  // libreria que permite establecer pines digitales
        // para comunicacion serie
#include <Braccio.h>
#include <Servo.h>

SoftwareSerial miBT(7, 8);  // pin 7 como RX, pin 8 como TX
char DATO = 0;      // variable para almacenar caracter recibido

#define Pecho 2
#define Ptrig 4
long duracion, distancia;

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;
int x=30;
Servo servo;
String estado;
int POT1 = 0;
int POTv = 0;

void setup() {
  Serial.begin(9600);
  //Analogicos como entrada
  pinMode(A0, INPUT);
  miBT.begin(38400);    // comunicacion serie entre Arduino y el modulo a 38400 bps
  Braccio.begin();
  pinMode(Pecho, INPUT);     // define el pin 6 como entrada (echo)
  pinMode(Ptrig, OUTPUT);    // define el pin 7 como salida  (triger)
  pinMode(13, OUTPUT);            // Define el pin 13 como salida
  Braccio.ServoMovement(30,0, 45, 180, 0, 0,  0); 
}

void loop() {
  digitalWrite(Ptrig, LOW);
  delayMicroseconds(2);
  digitalWrite(Ptrig, HIGH);   // genera el pulso de triger por 10ms
  delayMicroseconds(10);
  digitalWrite(Ptrig, LOW);
   duracion = pulseIn(Pecho, HIGH);
   distancia = (duracion/2) / 29;            // calcula la distancia en centimetros
  if (distancia >= 500 || distancia <= 0){  // si la distancia es mayor a 500cm o menor a 0cm 
    Serial.println("---");                  // no mide nada
  }
  else {
    Serial.print(distancia);           // envia el valor de la distancia por el puerto serial
    Serial.println("cm");              // le coloca a la distancia los centimetros "cm"
    digitalWrite(13, LOW);               // en bajo el pin 13
    miBT.println(distancia);
    delay(800); 
  } 
  
   if (distancia <= 10 && distancia >= 1){
    digitalWrite(13, HIGH);                     // en alto el pin 13 si la distancia es menor a 10cm
    Serial.println("Alarma.......");         // envia la palabra Alarma por el puerto serial
    Gel();
  }
  delay(400); 
  
  if (miBT.available()){      // si hay informacion disponible desde modulo
  delay(100);
  DATO = miBT.read();   // almacena en DATO el caracter recibido desde modulo
  //Serial.println(DATO);
  if( DATO == 'A' ) {  // si el caracter recibido es el numero 2
      delay(100);
      //Serial.println("Estado inicial");
      Braccio.ServoMovement(x,0, 45, 180, 0, 0,  70);
  }
  if( DATO == 'B' ){  // si el caracter recibido es el numero 1
      delay(1000);
      //Serial.println("Movimiento 1");
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
   if(DATO == 'C'){
      //Serial.println("Movimiento 2");
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
   if(DATO == 'D'){
      //Serial.println("Movimiento 3");
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
   if(DATO == 'E'){
      //Serial.println("Movimiento 4");
      delay(1000);
      //Inicio de movimiento
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
   }
  }
 }

 void Gel(){
     Serial.println("Movimiento 5");
     Braccio.ServoMovement(20,0, 45, 180, 0, 0,  0);
     Braccio.ServoMovement(20,0, 45, 180, 180, 90,  0);
     Braccio.ServoMovement(20,0, 45, 90, 180, 90,  0);
     delay(500);
     elbow.write(30);
     delay(500);
     elbow.write(90);
     Braccio.ServoMovement(30,0, 45, 90, 180, 90,  0);
     Braccio.ServoMovement(30,0, 45, 180, 180, 90,  0);
     Braccio.ServoMovement(20,0, 45, 180, 0, 0,  0);
     delay(1000);
  }
