const int motorPin = 3;
int on = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
}

void  shortVib()
{
  digitalWrite(motorPin, HIGH);    
  delay(300);
  digitalWrite(motorPin, LOW);
  delay(600);
}

void  turn_on()
{
  on = 1;
}

void  turn_off()
{
  on = 0;
}

void  error()
{
}

void serialEvent()
{
}

void  vibrate(int n)
{
  int x = 0;
  while (x < n)
  {
    shortVib();
    x++;
  }
}

void loop()
{
  if (Serial.available() > 0)
    {
      vibrate(Serial.read());
      delay(1000);
    }
}

