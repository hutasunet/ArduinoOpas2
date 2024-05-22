#define LED     7
#define SWITCH  6
#define BUZZER  3

#define NOTE_A4 440

void setup() {
     pinMode(LED, OUTPUT);
     pinMode(SWITCH, INPUT_PULLUP);
     pinMode(BUZZER,OUTPUT);
  }

void loop() 
{
  if(digitalRead(SWITCH)== LOW)
  {
    // kytkintä painettu
    digitalWrite(LED, HIGH);  // turn the LED on (HIGH is the voltage level)
    tone(BUZZER,NOTE_A4,500); // Play A4 note 
  }
  else
  {
    digitalWrite(LED, LOW);   // turn the LED off by making the voltage LOW
  }
}
