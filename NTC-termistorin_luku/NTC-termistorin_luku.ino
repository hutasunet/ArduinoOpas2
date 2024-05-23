#include "analogWave.h"

#define LED     7
#define SWITCH  6
#define BUZZER  3
#define TEMP_SENSOR  A1

#define TERMISTOR_NOMINAL_RESISTANCE  10000 // Resistanssi 25 asteessa
#define TEMPERATURE_NOMINAL 25
#define B_COEFF 3730 // Lämpötila-anturi: Epcos B57620C5102K062 
#define SERIESRESISTOR  9860

#define NOTE_A4 440

// Alustetaan DAC käyttöön
analogWave wave(DAC);

void setup() {
  // Sarjaportin alustus
  Serial.begin(9600);
  // I/O -alustus
  pinMode(LED, OUTPUT);
  pinMode(SWITCH, INPUT_PULLUP);
  pinMode(BUZZER,OUTPUT);
  // Asetetaan DAC 12-bitin moodiin
  analogWriteResolution(12);
  // Alustetaan siniaaltomuoto
  wave.sine(NOTE_A4);
  // Alustetaan AD-muunnin 12 bitin muotoon
  analogReadResolution(12);
}
void loop() 
{
 float t=readTemperature();
  Serial.print("Temperature is ");
  Serial.print(t,2);
  Serial.println(" Celsius.");

  if(digitalRead(SWITCH)== LOW)
  {
    // kytkintä painettu
    digitalWrite(LED, HIGH);  // led on
    //tone(BUZZER,NOTE_A4,500); // soitetaan saundi
    wave.freq(NOTE_A4); // soitetaan saundi
    delay(1000);
  }
  else
  {
    digitalWrite(LED, LOW);   // led off
    wave.stop();
  }
}
float readTemperature()
{
  float steinhart=0;
  float value =0; 
  float analogValue = analogRead(TEMPSENSOR);
  value = 4095 / analogValue - 1;
  value = SERIESRESISTOR / value;

  steinhart = value / TERMISTOR_NOMINAL_RESISTANCE;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= B_COEFF;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURE_NOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert absolute temp to C
  return steinhart;
}
