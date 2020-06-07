//////////////////////////////////////////////////////////////////
// Importando as bibliotecas necessárias e declaração de variáveis

//BMP200 pressao e altidude
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp; 
float pressao;
float altitude;

//////////////////////////////////////////////////////////////////

//DHT22 umidade
#include <DHT.h>; 
#include <Wire.h>
#define DHTPIN 4 
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE); 
float umidade;
float aU;
float bU;

//////////////////////////////////////////////////////////////////

//LDR luminosidade
const int ldrPin = A0;
float lux;
float Vout;
float RLDR;

//////////////////////////////////////////////////////////////////

//LM35 temperatura 
const int lmPin = A1;
float value;
float temperatura;
float aT;
float bT;

//////////////////////////////////////////////////////////////////

//LCD info
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
int lcdState;

//////////////////////////////////////////////////////////////////

//button
const int buttonPin = 2;
int current;
int last;

//////////////////////////////////////////////////////////////////

float dht22();
float lm35();
float ldr();
float bmp280p();
float bmp280h();

//////////////////////////////////////////////////////////////////

void setup() 
{
  lcd.begin (16,2); // Inicializando o lcd
  analogReference(INTERNAL);
  dht.begin(); // Inicializando o DHT22
  bmp.begin(0x76);// Inicializando o BMP280
  
  // Nomeando os pinos
  pinMode(lmPin, INPUT); 
  pinMode(ldrPin, INPUT);
  pinMode(buttonPin, OUTPUT);

  
  lcdState = 1; // Estado inicial do monitor
  last = digitalRead(buttonPin); // contador

}
//////////////////////////////////////////////////////////////////
// Definições das funções que serão utilizadas

//retorna a umidade
  float dht22()
  {
    aU = 1.020819677;
    bU = -2.784236918;
    umidade = aU * dht.readHumidity() + bU;
    return umidade;
  }

//retorna a temperatura
  float lm35()
  {
    aT = 99.62636965;
    bT = 0;
    float percent = analogRead(lmPin)/1023.0;
    float volts = percent * 1.1;
    temperatura = aT * volts + bT;
    return temperatura;
  }

//retorna a luminosidade
  float ldr()
  {
    value = analogRead(ldrPin);
    Vout = (value * 1.1)/1023.0; 
    RLDR = (200000.0 * Vout)/(3.3 - Vout);
    lux = pow(10, 5.0 - log10(RLDR));
    return lux;
  }

//retorna a pressão
  float bmp280p()
  {
    pressao = bmp.readPressure();
    return pressao;
  }

//retorna a altitude
  float bmp280h()
  {
    altitude = bmp.readAltitude(1013.25);
    return altitude;
  }

//////////////////////////////////////////////////////////////////

void loop() 
{
  
//////////////////////////////////////////////////////////////////
  lcd.setBacklight(HIGH);
  lcd.setCursor(7, 0);
  lcd.print("EM"); // "Estação Meteorológica"

  current = digitalRead(buttonPin);

///////////////////////////////////////////////////////////////////////////////
// Mecanismo que faz com que o botão fique apenas 1 vez em HIGH quando apertado

if ((current == LOW) && (last == HIGH)) 
{
  lcd.clear();
  
      if (lcdState < 5) 
     {
       lcdState = lcdState + 1;
     } 
     else 
     {
       lcdState = 1;
     }  
     
}

  last = current;
  
//////////////////////////////////////////////////////////////////
//roda a função do DHT22
  if (lcdState == 1)
  {
    lcd.setCursor(3,1);
    lcd.print("UR: ");
    lcd.print(dht22());
    lcd.print("%");
    Serial.println(dht22());
  }

//////////////////////////////////////////////////////////////////
//roda a função do LM35
  if (lcdState == 2)
  {
    lcd.setCursor(3,1);
    lcd.print("T: ");
    lcd.print(lm35());
    lcd.print((char)223);
    lcd.print("C");
    Serial.println(lm35());
  }

//////////////////////////////////////////////////////////////////
//roda a função do LDR
  if (lcdState == 3)
  {
    lcd.setCursor(1,1);
    lcd.print("lumi: ");
    lcd.print(ldr());
    lcd.print("Lux");
    Serial.println(ldr());
  }

//////////////////////////////////////////////////////////////////
//roda a função do BMP280p
  if (lcdState == 4)
  {
    lcd.setCursor(2,1);
    lcd.print(F("P: "));
    lcd.print(bmp280p()/100.0);
    lcd.print("hPa");
    Serial.println(bmp280p());
  }  

//////////////////////////////////////////////////////////////////
//roda a função do BMP280h
  if (lcdState == 5)
  {
    lcd.setCursor(3,1);
    lcd.print(F("H: "));
    lcd.print(bmp280h());
    lcd.print("m");
    Serial.println(bmp280h());
  }  
//////////////////////////////////////////////////////////////////
 delay(200);
}
