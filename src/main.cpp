#include <Arduino.h>

#include <TimerOne.h>

#define ledpin 13 // светодиод
#define sensorpin 2 //подключение датчика Движения
#define lightpin A0 //подключение датчика освещения

int lightTime = 0;

void doClock()  { //обработчик прерываний от часов (ежесекундно)
  if (lightTime > 0) lightTime--;
} 

void setup() {
  pinMode(ledpin, OUTPUT);
  pinMode(sensorpin, INPUT);
  digitalWrite(ledpin, LOW);
  
  Timer1.initialize(1000000); // Timer0 interrupt - set a timer of length 1000000 microseconds
  Timer1.attachInterrupt(doClock); // attach the service routine here
}

void loop() {
  if (digitalRead(sensorpin) & analogRead(lightpin) < 50 ){
    lightTime = 60;
  }
  if (lightTime > 0 & analogRead(lightpin) < 50) {
    digitalWrite(ledpin, HIGH);
  }
  else {
    digitalWrite(ledpin, LOW);
    lightTime = 0;
  }
}