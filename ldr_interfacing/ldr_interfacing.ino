#define ldr_qty 7
#define fet_gate 9

const int ldr_pins[] = {2, 3, 4, 5, 6, 7, 8};
const int planet_sounds[] = {2000, 2250, 2500, 2750, 3000, 3500, 4000};

void setup()
{
  Serial.begin(9600);
  pinMode(fet_gate, OUTPUT);
  for (int i = 0; i < ldr_qty; i++)
  	pinMode(ldr_pins[i], INPUT);
}


void loop()
{
  bool ldr_on = false;
  for (int i = 0; i < ldr_qty; i++)
  {
    if (digitalRead(ldr_pins[i]) == 0)
    {
      tone(fet_gate, planet_sounds[i]);
      ldr_on = true;
      break;
    }
  }
  
  if (!ldr_on)
  	noTone(fet_gate);
  

  delay(100);
}
