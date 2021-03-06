/*
    Projeto Final - Estação Meteorológica
    Curso: Instrumentação e Medição
    @Autor: Francisco Janela - 1C
    @Professor: Fabio Ferraz Junior
 */
 
/////////////// BIBLIOTECAS E VARIAVEIS //////////////////
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


//////////////////// SETUP DO CÓDIGO //////////////////////
void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL);
  
  //LCD:
  lcd.begin(16,2);
  
  //TMP 36:
  pinMode(A0, INPUT);
  
  //DHT 22:
  dht.begin();
  
  //LDR:
  pinMode(A1, INPUT);
  
}

///////////////// DEFININDO SUB-ROTINAS ///////////////////
// Sub-rotina do TMP com calibração:
float TMP_celsiusCalibrado() {
  TMPsensorValue = analogRead(A0);                  // leitura do sensor
  TMPtensao = (TMPsensorValue*1.1)/1023.0;          // conversão para tensão
  TMPcelsius = 99.62636965*TMPtensao-49.75568659;   // conversão para graus Celsius com calibração
  return TMPcelsius;
}

// Sub-rotina do DHT22 com calibração:
float DHT_umidadeCalibrado() {
  DHTumidade = 1.020819677*dht.readHumidity()-2.784236918;  // calibração da medição
  return DHTumidade;
}

// Sub-rotina do LDR:
float LDR_luminosidade() {
  LDRsensorValue = analogRead(A1);                         // leitura do sensor
  LDRtensao = (LDRsensorValue/1023.0)*1.1;                 // conversão para tensao
  LDRresistencia = (LDRtensao*184000.0)/(3.3-LDRtensao);   // conversão para resistência
  LDRluminosidade = pow(10,5.0-log10(LDRresistencia));     // conversão para luminosidade
  return LDRluminosidade;
}


////////////////// ROTINA PRINCIPAL //////////////////////
void loop() {
  // print TMP36:
  lcd.clear();
  lcd.print("Temperatura [C]:");
  lcd.setCursor(5,1);
  lcd.print(TMP_celsiusCalibrado());
  Serial.print("\nTemperatura [C]: ");
  Serial.println(TMP_celsiusCalibrado());
  delay(2000);

  // print DHT22:
  lcd.clear();
  lcd.print("Umidade [%]:");
  lcd.setCursor(5,1);
  lcd.print(DHT_umidadeCalibrado());
  Serial.print("\nUmidade [%]: ");
  Serial.println(DHT_umidadeCalibrado());
  delay(2000);

  //print LDR:
  lcd.clear();
  lcd.print("Lumino [Lux]:");
  lcd.setCursor(5,1);
  lcd.print(LDR_luminosidade());
  Serial.print("\nLuminosidade [Lux]: ");
  Serial.println(LDR_luminosidade());
  delay(2000);
}
