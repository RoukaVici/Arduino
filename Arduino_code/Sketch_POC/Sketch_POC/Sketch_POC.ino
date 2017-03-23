const int first = 3;
const int motors = 1;

void setup()
{
  // Init serial connection
  Serial.begin(9600);

  // Init all motors starting from 'first'
  int i = 0;
  while (i < motors)
  {
    pinMode(i + first, OUTPUT);
    i++;
  }
}

void  shortVib()
{
  delay(300);
  digitalWrite(first, LOW);
  delay(600);
}

void modify(char num, char state)
{
  digitalWrite(first + num, state == 1 ? HIGH : LOW);
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

void  error()
{
  vibrate(3);
}

void serialEvent()
{
  // If there are 2 bytes available to read
  if (Serial.available() > 1)
    {
      char buff[2];
      // Put them in buffer
      Serial.readBytes(buff, 2);
      // If the motor number is valid, modify its state
      if (buff[0] < motors && buff[0] >= 0)
        modify(buff[0], buff[1]);
      else
        error();
    }
}

void loop()
{
}

