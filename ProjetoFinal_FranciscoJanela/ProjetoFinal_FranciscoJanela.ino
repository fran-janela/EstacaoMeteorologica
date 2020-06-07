/*
    Projeto Final - Estação Metereológica
    Curso: Instrumentação e Medição
    @Autor: Francisco Janela - 1C
    @Professor: Fabio Ferraz Junior
 */
 
////////////// Bibliotecas e Variáveis ///////////////
// Liquid Crystal Display:
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// TMP 36:
float TMPcelsius = 0.0;
int TMPsensorValue;
float TMPtensao;


// DHT 22:
#include "DHT.h"

#define DHTPIN 7
#define DHTTYPE DHT22

DHT dht(DHTPIN,DHTTYPE);

float DHTumidade;


//LDR:
int LDRsensorValue;
float LDRtensao, LDRresistencia, LDRluminosidade;


/////////////////// SETUP DO CÓDIGO /////////////////////
void setup() {
  Serial.begin(9600);
  //LCD:
  //TMP 36:
  //DHT 22:
  //LDR:

}

void loop() {
  // put your main code here, to run repeatedly:

}
