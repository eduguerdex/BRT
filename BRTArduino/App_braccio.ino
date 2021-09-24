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
#define BUZZER 13

void setup() {
  Serial.begin(9600);
  //Analogicos como entrada
  pinMode(A0, INPUT);
  miBT.begin(38400);    // comunicacion serie entre Arduino y el modulo a 38400 bps
  Braccio.begin();
  pinMode(Pecho, INPUT);     // define el pin 6 como entrada (echo)
  pinMode(Ptrig, OUTPUT);    // define el pin 7 como salida  (triger)
  pinMode(BUZZER, OUTPUT);            // Define el pin 13 como salida
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
    noTone(BUZZER);               // en bajo el pin 13
    miBT.println(distancia);
    delay(800); 
  } 
  
   if (distancia <= 10 && distancia >= 1){
    Serial.println("Alarma.......");         // envia la palabra Alarma por el puerto serial
    GATO();
  }
  delay(400); 
  
  if (miBT.available()){      // si hay informacion disponible desde modulo
  delay(100);
  DATO = miBT.read();   // almacena en DATO el caracter recibido desde modulo
  //Serial.println(DATO);
  if( DATO == 'A' ) {  // si el caracter recibido es el numero 2
      INICIO();
  }
  if( DATO == 'B' ){  // si el caracter recibido es el numero 1
      MOV1();
  }
   if(DATO == 'C'){
      MOV2();
   }
   if(DATO == 'D'){
      MOV3();
   }
   if(DATO == 'E'){
      MOV4();
   }
   if(DATO == 'F'){
     MOV5();
   }
   if(DATO == 'G'){
     MOV6();
   }
   if(DATO == 'H'){
     PASE();
   }
   if(DATO == 'I'){
     GOL();
   }
   if(DATO == 'J'){
     POSE1();
   }
   if(DATO == 'K'){
     POSE2();
   }
   if(DATO == 'L'){
     POSE3();
   }
   if(DATO == 'M'){
     GATO();
   }
  }
 }

 void GEL(){
     Serial.println("Movimiento 5");
     Braccio.ServoMovement(20,0, 45, 180, 0, 0,  0);
     Braccio.ServoMovement(20,0, 65, 180, 180, 90,  0);
     Braccio.ServoMovement(20,0, 65, 90, 180, 90,  0);
     delay(500);
     elbow.write(25);
     delay(500);
     elbow.write(90);
     Braccio.ServoMovement(30,0, 65, 90, 180, 90,  0);
     Braccio.ServoMovement(30,0, 65, 180, 180, 90,  0);
     Braccio.ServoMovement(20,0, 45, 180, 0, 0,  0);
     delay(1000);
  }

  void PASE(){
      Serial.println("Movimiento pase");
      delay(1000);
      //Inicio de movimiento
      Braccio.ServoMovement(20,0, 45, 180, 0, 0,  0); 
      Braccio.ServoMovement(20,50, 45, 180, 180, 0,   0);
      Braccio.ServoMovement(20,50, 78, 180, 180, 0,   0);
      //Inicio de movimiento 2 180  0
      Braccio.ServoMovement(20,50, 78, 180, 180, 0,   100);
      Braccio.ServoMovement(20,50, 45, 180, 180, 0,   100);   
      Braccio.ServoMovement(20,90, 95, 95, 90, 90,  100);
      Braccio.ServoMovement(20,0, 45, 180, 0, 0,  100);    
      Braccio.ServoMovement(10,0, 45, 180, 40, 0,  100);
      Braccio.ServoMovement(20,100, 45, 180, 180, 0,   100);
      Braccio.ServoMovement(30,100, 90, 180, 160, 0,   100);
      Braccio.ServoMovement(30,100, 95, 180, 160, 0,   0);
      Braccio.ServoMovement(10,100, 95, 180, 180, 0,   0);
      Braccio.ServoMovement(10,100, 75, 180, 180, 0,   100);
      Braccio.ServoMovement(10,100, 75, 180, 45, 0,   100);
      Braccio.ServoMovement(30,0, 45, 180, 0, 0,  0); 
  }
  void GOL(){
      Serial.println("Movimiento GOL");
      delay(1000);
      //Inicio de movimient
      Braccio.ServoMovement(20,0, 45, 180, 0, 0,  0); 
      Braccio.ServoMovement(20,85, 90, 90, 90, 0,  0); 
      Braccio.ServoMovement(20,60, 93, 90, 0, 0,  0);
      Braccio.ServoMovement(20,60, 93, 0, 0, 0,  0);
      Braccio.ServoMovement(20,60, 93, 0, 0, 90,  0);
      Braccio.ServoMovement(20,60, 93, 0, 0, 90,  100);
      Braccio.ServoMovement(20,90, 130, 20, 0, 90,  100);
      Braccio.ServoMovement(20,90, 130, 20, 0, 90,  100);
      Braccio.ServoMovement(20,90, 70, 20, 0, 0,  100);
      Braccio.ServoMovement(10,90, 70, 90, 90, 0, 100);
      Braccio.ServoMovement(10,90, 70, 90, 90, 0, 100);
      Braccio.ServoMovement(10,90, 110, 160, 0, 0,  0);
      Braccio.ServoMovement(20,0, 90, 90, 90, 0,  100);
      Braccio.ServoMovement(30,0, 45, 180, 0, 0,  0);   
  }
  void POSE1(){
      Serial.println("POSE 1");
      delay(1000);
      //Inicio de movimient
      Braccio.ServoMovement(20,85, 90, 125, 60, 0,  0); 
  }
  void POSE2(){
      Serial.println("POSE 1");
      delay(1000);
      //Inicio de movimient
      Braccio.ServoMovement(20,25, 40, 185, 80, 0,  0); 
  }
  void POSE3(){
      Serial.println("POSE 1");
      delay(1000);
      //Inicio de movimient
      Braccio.ServoMovement(20,155, 90, 125, 180, 0,  70); 
  }
  void POSE4(){
      Serial.println("POSE 1");
      delay(1000);
      //Inicio de movimient
      Braccio.ServoMovement(20,95, 90, 95, 140, 60,  0); 
  }
  void INICIO(){
      delay(100);
      Serial.println("Estado inicial");
      Braccio.ServoMovement(x,0, 45, 180, 0, 0,  70);
  }
  void MOV1(){
      delay(1000);
      Serial.println("Atrapa Vaso");
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
  void MOV2(){
      Serial.println("MUEVE TORRE");
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
  void MOV3(){
      Serial.println("Ordena Torre");
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
  void MOV4(){
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
   void MOV5(){
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
   void MOV6(){
     Serial.println("Movimiento 6");
     Braccio.ServoMovement(20,0, 45, 180, 0, 0,  0);
     Braccio.ServoMovement(20,90, 90, 90, 90, 90,  0);
     delay(1000);
     }
   void GATO(){
     Serial.println("Movimiento 6");
     Braccio.ServoMovement(20,0, 45, 180, 0, 0,  0);
     tone(BUZZER,650);
     Braccio.ServoMovement(20,0, 85, 180, 180, 0,  0);
     tone(BUZZER,850);
     Braccio.ServoMovement(20,0, 85, 180, 180, 0,  100);
     tone(BUZZER,950);
     Braccio.ServoMovement(20,0, 85, 180, 90, 90,  100);
     tone(BUZZER,550);
     Braccio.ServoMovement(20,10, 85, 180, 90, 90,  100);
     tone(BUZZER,650);
     Braccio.ServoMovement(20,180,85, 180, 90, 90,  100);
     tone(BUZZER,750);
     Braccio.ServoMovement(20,0, 85, 180, 90, 90,  100);
     tone(BUZZER,850);
     Braccio.ServoMovement(20,0, 85, 180, 180, 0,  100);
     tone(BUZZER,950);
     Braccio.ServoMovement(30,0, 85, 180, 180, 0,  0);
     tone(BUZZER,1050);
     Braccio.ServoMovement(20,0, 45, 180, 0, 0,  0);
     tone(BUZZER,1650);
     delay(1000);
     }
