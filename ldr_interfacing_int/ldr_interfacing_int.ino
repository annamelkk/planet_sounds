#define ldr_qty 3
#define fet_gate 9

// const int ldr_pins[] = {2, 3, 4, 5, 6, 7, 8};
const int ldr_pins[] = {2, 3, 8};
const int planet_sounds[] = {262, 294, 330};
// const int planet_sounds[] = {262, 294, 330, 349, 392, 440, 494};
volatile int active_ldr = -1;

void handler()
{
  for (int i = 0; i < ldr_qty; i++)
  {
    if (digitalRead(ldr_pins[i]) == 1)
    {
      active_ldr = i; // save LDR index in i
      return;
    }
  }
  active_ldr = -1; // reset active value for later
}

void setup()
{
  Serial.begin(9600);
  pinMode(fet_gate, OUTPUT);
  for (int i = 0; i < ldr_qty; i++)
  {
  	pinMode(ldr_pins[i], INPUT);
    attachInterrupt(digitalPinToInterrupt(ldr_pins[i]), handler, CHANGE);
  }
}


void loop()
{
  if (active_ldr >= 0)
    tone(fet_gate, planet_sounds[active_ldr]);
  else
    noTone(fet_gate);
  delay(100);
}
