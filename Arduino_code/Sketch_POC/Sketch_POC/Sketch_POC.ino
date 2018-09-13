const int motors = 5;
const int tab[motors] = {6, 7, 8, 9, 10};
// The API level we're using
char apiLevel = 1;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    Serial.println("Waiting for serial port connection...");// wait for serial port to connect. Needed for Leonardo only
  }
 
  Serial.println("Ready!");
  
  // Init all motors
  int i = 0;
  while (i < motors)
  {
    pinMode(tab[i], OUTPUT);
    i++;
  }
}

void  shortVib()
{
  digitalWrite(tab[0], HIGH);
  delay(300);
  digitalWrite(tab[0], LOW);
  delay(600);
}

// Change a motor's state.  Motor is #num, and we write value 'val' to it.
void modify(char num, char val)
{
  if (num < motors)
    analogWrite(tab[num], val);
}

// Do n short vibrations
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

void  v

void handleVibrationv1(const char* buff)
{
    // If the motor number is valid, modify its state
    if (buff[0] < motors && buff[0] >= 0)
      modify(buff[0], buff[1]);
    else
    {
      error();
    }
 
}
int readFromSerial()
{
  // This char tells us how much data we're expecting. 0 means we're expecting a header
  static char expectingData = 0;

  // We're expecting to read data and there's enough data available
  if (expectingData && Serial.available() >= expectingData)
  {
    char buff[expectingData];
    Serial.readBytes(buff, expectingData);
    expectingData = 0;
    if (apiLevel == 1)
    {
      handleVibrationv1(buff);
    }
  }
  // If there are 3 bytes available to read (packet header)
  else if (Serial.available() >= 3)
  {
    char buff[3];
    Serial.readBytes(buff, 3);
    if (buff[0] == 'H')
    {
      // Handshake packet, we only support APIv1 (the lowest possible value) so we just need to check the min value
      if (buff[1] == apiLevel)
      {
        // Write ['H', 1] to confirm we want API level 1
        Serial.write(buff, 2);
      }
      else
      {
        buff[0] = 'X';
        buff[1] = 0;
        // Write ['H', 0] to signify that the handshake has failed
        Serial.write(buff, 2);
      }
    }
    else if (buff[0] == 'R' && buff[1] == apiLevel)
    {
      // Vibration packet, right api Level, we can read incoming data
      expectingData = buff[2];
    }
    else
    {
      // Invalid packet. Error
      error();
    }
  }
  // Return 1 if there's another packet we can read, 0 otherwise
  return (expectingData > 0 && Serial.available() >= expectingData) || Serial.available() >= 3 ? 1 : 0;
}

// Triggers every time something happens on the serial connection
void serialEvent()
{
  // readFromSerial returns 1 if there's another valid packet already queued up
  while (readFromSerial() != 0);  
}

void loop() // run over and over
{
  
}
