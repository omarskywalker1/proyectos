#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define Menu 0
#define Lavado 1
#define Enjuagado 2
#define Centrifugado 3
#define tLavado  15
#define tEnjuagado  3
#define tCentrifugado  1
//Inicializando funciones
int entrada(boolean l, boolean e, boolean c );
int lavado(int minutos);
int enjuagado(int minutos);
int centrifugado(int minutos);
void imprimeTiempo(int minutos);
//Inicializando variables globales
int fase = Menu; //Controlar fase por entrada
int reset = 0;
int entradaL = 10, entradaE = 11, entradaC = 12;
int salidaLavado = 13 , salidaEnjuagado = 8 ,salidaCentrifugado = 9;
//Inicializando LCD
LiquidCrystal_I2C lcd(0x27,20,4);

void setup(){
  pinMode(entradaL, INPUT);
  pinMode(entradaE, INPUT);
  pinMode(entradaC, INPUT);
  pinMode(salidaLavado, OUTPUT);
  pinMode(salidaEnjuagado, OUTPUT);
  pinMode(salidaCentrifugado, OUTPUT);
  lcd.init();
  lcd.begin(0x27,20,4);
  lcd.backlight();
  }

void loop(){
  fase = entrada(digitalRead(entradaL),digitalRead(entradaE),digitalRead(entradaC));
  switch(fase){
    case Lavado:
      reset = lavado(tLavado);
      fase = reset;
      break;
    case Enjuagado:
      reset = enjuagado(tEnjuagado);
      fase = reset;
      break;
    case Centrifugado:
      reset = centrifugado(tCentrifugado);
      fase = reset;
      break;
    default:
      menu();
      break;
  }
}
//Funcion para leer enmtradas
int entrada(boolean l, boolean e, boolean c ){
  if(l == HIGH && e == LOW && c == LOW){
    return Lavado;
  }else if (l == LOW && e == HIGH && c == LOW){
    return Enjuagado;
  } else if(l == LOW && e == LOW && c == HIGH){
    return Centrifugado;
  } else {
   return Menu; 
  }
}

//Funcion de menu al inicio
void menu(){
  lcd.setCursor(0,0);
  lcd.print("Menu de Inicio");
  lcd.setCursor(0,1);
  lcd.print("Opciones...");
}

//Funcion para imprimir tiempo
void imprimeTiempo(int minutos, int segundos){
  if(minutos < 10){
    if(segundos % 60 < 10){
      lcd.print("0"+String(minutos)+":0"+String(segundos%60));
    }else{
      lcd.print("0"+String(minutos)+":"+String(segundos%60));
    }
  }else{
    if(segundos % 60 < 10){
      lcd.print(String(minutos)+":0"+String(segundos%60));
    }else{
      lcd.print(String(minutos)+":"+String(segundos%60));
    }
  }
}

//Funcion de lavado
int lavado(int minutos){
  int segundos = minutos * 60;
  lcd.clear();
  while(segundos > 0){
     lcd.setCursor(0,0);
     lcd.print("Lavando...");
     lcd.setCursor(0,1);
     imprimeTiempo(minutos, segundos);
     //Restamos minutos
     if(segundos % 60 == 0){
      minutos -= 1;
     }
     //Salida
     digitalWrite(salidaLavado,HIGH);
     delay(1000);
     segundos -= 1;
  }
 digitalWrite(salidaLavado, LOW);
 return Menu;
}

//Funcion de secado
int enjuagado(int minutos){
  int segundos = minutos * 60;
  lcd.clear();
  while(segundos > 0){
     lcd.setCursor(0,0);
     lcd.print("Secando...");
     lcd.setCursor(0,1);
     imprimeTiempo(minutos, segundos);
     //Restamos minutos
     if(segundos % 60 == 0){
      minutos -= 1;
     }
     //Salida
     digitalWrite(salidaEnjuagado,HIGH);
     delay(1000);
     segundos -= 1;
  }
 digitalWrite(salidaEnjuagado, LOW);
 return Menu;
}

//Funcion de centrifugado
int centrifugado(int minutos){
  int segundos = minutos * 60;
  lcd.clear();
  while(segundos > 0){
     lcd.setCursor(0,0);
     lcd.print("Cntrifugando...");
     lcd.setCursor(0,1);
     imprimeTiempo(minutos, segundos);
     //Restamos minutos
     if(segundos % 60 == 0){
      minutos -= 1;
     }
     //Salida
     digitalWrite(salidaCentrifugado,HIGH);
     delay(1000);
     segundos -= 1;
  }
 digitalWrite(salidaCentrifugado, LOW);
 return Menu;
}


 
