#define ldr_qty 3
#define fet_gate 5
#define pot_out A4

int pot_val = 0;
int volume = 0;
const int ldr_pins[] = {2, 3, 8, 8, 12, 13, 16, 17};
const int planet_sounds[] = {262, 294, 330, 349, 392, 440, 494};
volatile int active_ldr = -1; // 0 is an index as well so we set to safe negative value

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
  pinMode(pot_out, INPUT);
  for (int i = 0; i < ldr_qty; i++)
  {
  	pinMode(ldr_pins[i], INPUT);
    attachInterrupt(digitalPinToInterrupt(ldr_pins[i]), handler, CHANGE);
  }
  
}


void loop()
{  
  pot_val = analogRead(pot_out);
  Serial.print("Potentiometer ");
  Serial.println(pot_val);

  // volume = map(pot_val, 0, 1023, 10, 255);
  volume = pow((float)pot_val / 1023.0, 2) * 255;
  Serial.print("Mapped Volume ");
  Serial.println(volume);
  if (active_ldr >= 0) 
  {
    analogWrite(fet_gate, volume); 
    delayMicroseconds(1000000 / (2 * planet_sounds[active_ldr]));
  }
  else 
  {
    analogWrite(fet_gate, 0);
    delayMicroseconds(1000000 / (2 * planet_sounds[active_ldr]));
  }
}
