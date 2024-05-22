#include "analogWave.h"

#define LED     7
#define SWITCH  6
#define BUZZER  3

#define NOTE_A4 440

// Alustetaan DAC käyttöön
analogWave wave(DAC);

void setup() {
  // I/O -alustus
  pinMode(LED, OUTPUT);
  pinMode(SWITCH, INPUT_PULLUP);
  pinMode(BUZZER,OUTPUT);
  // Asetetaan DAC 12-bitin moodiin
  analogWriteResolution(12);
  // Alustetaan siniaaltomuoto
  wave.sine(NOTE_A4);
}

// the loop function runs over and over again forever
void loop() 
{
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
