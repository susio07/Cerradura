#include <LiquidCrystal.h>
#include <IRremote.h>
#include <Servo.h>

#define COLS 16 // Columnas del LCD
#define ROWS 2 // Filas del LCD

LiquidCrystal lcd(7, 9, 5, 4, 3, 2);

const int RECV_PIN = 8;
const int buzzer = 13;
const int ledVerde = 12;
const int ledRojo = 11;

const long KEY_1 = 0xE0E020DF;
const long KEY_2 = 0xE0E0A05F;
const long KEY_3 = 0xE0E0609F;
const long KEY_4 = 0xE0E010EF;
const long KEY_5 = 0xE0E0906F;
const long KEY_6 = 0xE0E050AF;
const long KEY_7 = 0xE0E030CF;
const long KEY_8 = 0xE0E0B04F;
const long KEY_9 = 0xE0E0708F;
const long KEY_0 = 0xE0E08877;
const long KEY_OK = 0xE0E016E9;
const long KEY_POWER = 0xE0E040BF;

bool estado = false; //cerrado
int clave[4] = { 0, 0, 0, 0};
int cont=0,i;

IRrecv irrecv(RECV_PIN);
decode_results results;

int claveCorrecta[4] = { 1, 5, 7, 3};
int pos=0;
Servo servo;

void centrar(){
  servo.write(pos);
}

void recibePulsacion (int cont){
  lcd.setCursor(cont,0);
  lcd.print("*");
  digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);
}

void abrir() {
   for (pos = 135; pos >= 15; pos -= 1) { 
      servo.write(pos);              
      delay(15);                       
  }
}

void cerrar() {
   for (pos = 15; pos <= 135; pos += 1) { 
      servo.write(pos);              
      delay(15);                       
  }
}

int compruebaClave (int pass[]){
  int i,result=0;
  for(i=0;i<=3;i++){   
      if (pass[i] != claveCorrecta[i]){
        result=1;         
      }    
  }
  return result;
}

void claveAfirmativa (){
    Serial.println("Clave Correcta!!!"); 
    lcd.setCursor(0,0);
    lcd.print("CLAVE CORRECTA");
    digitalWrite(buzzer,HIGH);
    delay(50);
    digitalWrite(buzzer,LOW);
    delay(50);
    digitalWrite(buzzer,HIGH);
    delay(50);
    digitalWrite(buzzer,LOW);
    digitalWrite(ledVerde, HIGH);
    delay(500);
    digitalWrite(ledVerde, LOW);
    lcd.clear();     
}

void claveIncorrecta (){
    lcd.setCursor(0,0);
    Serial.println("clave incorrecta"); 
    lcd.print("INCORRECTO");
    delay(500);
    lcd.clear();
    digitalWrite(ledRojo, HIGH);
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    delay(50);
    digitalWrite(ledRojo, LOW); 
}

 
void setup(){
   Serial.begin(9600);
   irrecv.enableIRIn();
   pinMode(ledVerde , OUTPUT);
   pinMode(ledRojo , OUTPUT);
   pinMode(buzzer,OUTPUT);
   servo.attach(10);
  // Configuramos las filas y las columnas del LCD en este caso 16 columnas y 2 filas
  lcd.begin(COLS, ROWS); 
  servo.write(135); 
}
 
void loop(){ 

 // centrar();
  int inicial = servo.read();
   if (irrecv.decode(&results)){
    switch (results.value){
      case KEY_OK:
        Serial.println("KEY_OK");
        lcd.setCursor(0,0);
        lcd.print("KEY OK");
        if (compruebaClave(clave) == 0){
            claveAfirmativa();
            abrir();
            estado = true; //abierto
            cont=0;
            clave[0] = 0;
        } else {
            claveIncorrecta();
            cont=0;
            clave[0] = 0;
        }
        break;
      case KEY_1:
          recibePulsacion(cont);
          clave[cont]=1;
          cont++;
          break;
      case KEY_2:
          recibePulsacion(cont);
          clave[cont]=2;
          cont++;
          break;
      case KEY_3:
          recibePulsacion(cont);
          clave[cont]=3;
          cont++;
          break;
      case KEY_4:
          recibePulsacion(cont);
          clave[cont]=4;
          cont++;
          break;
      case KEY_5:
          recibePulsacion(cont);
          clave[cont]=5;
          cont++;
          break;
      case KEY_6:
          recibePulsacion(cont);
          clave[cont]=6;
          cont++;
          break;
      case KEY_7:
          recibePulsacion(cont);
          clave[cont]=7;
          cont++;
          break;
      case KEY_8:
          recibePulsacion(cont);
          clave[cont]=8;
          cont++;
          break;
      case KEY_9:
          recibePulsacion(cont);
          clave[cont]=9;
          cont++;
          break;
      case KEY_0:
          recibePulsacion(cont);
          clave[cont]=0;
          cont++;
          break;
      case KEY_POWER:
          if (estado == true){
            cerrar();
            estado = false; //cerrado
          }
          break;
      default: 
       // Serial.println("Te trollee");
        lcd.setCursor(cont,0);
        lcd.print("?");
        break;
    }
      irrecv.resume();
  }
}
