#define LIGHT A0
#define LEDRP 13
#define LEDVP 12
#define BUTTON 11
#define BUZZER 5
#define LEDVA 4
#define LEDAA 3
#define LEDRA 2

int TiempoCruce = 5000; 
unsigned long TiempoCambio = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LIGHT, INPUT);
  pinMode(BUTTON, INPUT);
  pinMode(LEDRP,OUTPUT);
  pinMode(LEDVP,OUTPUT); 
  pinMode(LEDRA,OUTPUT);
  pinMode(LEDVA,OUTPUT); 
  pinMode(LEDAA,OUTPUT); 
  pinMode(BUZZER,OUTPUT); 
  digitalWrite(LEDVA,HIGH);
  digitalWrite(LEDAA,LOW);
  digitalWrite(LEDRA,LOW);
  digitalWrite(LEDVP,LOW);
  digitalWrite(LEDRP,HIGH);
}

void loop() {
  int lecbot= digitalRead(BUTTON);
  int lecLuz=analogRead(LIGHT);
  int mapLuz=map(lecLuz,0,1023,0,100);
  
  Serial.println("--------");
  Serial.print("LUZ: ");
  Serial.println(mapLuz);
  Serial.print("Boton: ");
  Serial.println(lecbot);
  Serial.println("--------");

  if( mapLuz <= 50  ){  // NOCHE
     noche();
  }
  else{
    if( lecbot == 1 && (millis() - TiempoCambio) > 5000 ){  // si el caracter recibido es el numero 1
        peaton();
        }
    else{
      digitalWrite(LEDVA,HIGH);
      digitalWrite(LEDRP,HIGH);
      delay(2000);
      digitalWrite(LEDVA,LOW);
      digitalWrite(LEDRA,LOW);
      digitalWrite(LEDAA,HIGH);
      delay(1000);
      digitalWrite(LEDAA,LOW);
      digitalWrite(LEDRA,HIGH);
      digitalWrite(LEDRP,LOW);
      digitalWrite(LEDVP,HIGH);
      tone(BUZZER,800);
      delay(2000); 
      noTone(BUZZER);
      digitalWrite(LEDVP,LOW);
      digitalWrite(LEDRA,LOW);
      digitalWrite(LEDVA,HIGH);
      digitalWrite(LEDRP,HIGH);     
      }
    }
}

void noche(){
    noTone(BUZZER);
    digitalWrite(LEDVA,LOW);
    digitalWrite(LEDAA,LOW);
    digitalWrite(LEDVP,LOW);
    digitalWrite(LEDRP,LOW);

    for (int x=0; x<10; x++) {
      digitalWrite(LEDRA,HIGH);
      delay(250);
      digitalWrite(LEDRA,LOW);
      delay(250);
    }
}

void peaton(){
    digitalWrite(LEDVA,LOW);
    digitalWrite(LEDAA,HIGH);
    delay(1000);
    digitalWrite(LEDAA,LOW);
    digitalWrite(LEDRA,HIGH);
    delay(500);
    digitalWrite(LEDVP,HIGH);
    digitalWrite(LEDRP,LOW);
    delay(TiempoCruce);

    for (int x=0; x<10; x++) {
      digitalWrite(LEDVP,HIGH);
      delay(250);
      digitalWrite(LEDVP, LOW);
      delay(250);
    }
    digitalWrite(LEDRP, HIGH);
    delay(500);
    digitalWrite(LEDAA, HIGH);
    digitalWrite(LEDRA, LOW);
    delay(1000);
    digitalWrite(LEDVA, HIGH);
    digitalWrite(LEDAA, LOW);
    TiempoCambio = millis();
    
}
