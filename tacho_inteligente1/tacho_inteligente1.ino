//librerias
#include <Servo.h>

//el tacho medirá 300 cm para hacer las pruebas.
// leds
int amarillo = 3;   //normal
int verde = 5;    //medio lleno
int rojo = 4;   //lleno

//ultrasonico de Tapa
int echoTapa = 6;
int triggerTapa = 7;
int tiempoTapa;
int distanciaTapa;

//ultrasonico de Persona -> cuando se acerca una persona al tacho
int echoPersona = 9;
int triggerPersona = 8;
int tiempoPersona;
int distanciaPersona;

//Servomotor
Servo servo;

void setup(){
  //leds
  pinMode(amarillo, OUTPUT);
  pinMode(rojo, OUTPUT);
  pinMode(verde, OUTPUT);
  
  //ultrasonicos
  pinMode(echoTapa, INPUT);
  pinMode(triggerTapa, OUTPUT);
  pinMode(echoPersona, INPUT);
  pinMode(triggerPersona, OUTPUT);
  Serial.begin(9600);
  
  //servo
  servo.attach(10); //pin 10 para servo
}


void loop()
{
  digitalWrite(triggerTapa, HIGH);
  delay(100);
  digitalWrite(triggerTapa, LOW);
  
  tiempoTapa = pulseIn(echoTapa, HIGH);   //obtenemos el ancho del pulso
  distanciaTapa = tiempoTapa/59;          //escalamos el tiempo a una distancia en cm
  delay(100);
  
  //Funcionamiento de la alerta
  //normal/vacio
  if(distanciaTapa>=200 & distanciaTapa<300){
    Serial.println("NORMAL/VACIO");
  digitalWrite(amarillo, HIGH);
    digitalWrite(rojo, LOW);
    digitalWrite(verde,LOW);
  }
  
  //medio lleno
  else if(distanciaTapa>=100 & distanciaTapa<200){
    Serial.println("MEDIO LLENO");
    digitalWrite(verde, HIGH);
    digitalWrite(rojo, LOW);
    digitalWrite(amarillo, LOW);
  }
  
  //lleno
  else if(distanciaTapa<100){
    Serial.println("LLENO");
    digitalWrite(rojo, HIGH);
    digitalWrite(verde, LOW);
    digitalWrite(amarillo,LOW);
  }
  /* -------------------------------- */
  digitalWrite(triggerPersona, HIGH);
  delay(100);
  digitalWrite(triggerPersona, LOW);
  
  tiempoPersona = pulseIn(echoPersona, HIGH);   //obtenemos el ancho del pulso
  distanciaPersona = tiempoPersona/59;         //escalamos el tiempo a una distancia en cm
  delay(100);
  //Funcionamiento de apertura de tapa -> se acerca alguien
  if(distanciaPersona<=150){
    servo.write(90);
  }
  else{
    servo.write(0);
  }
}
