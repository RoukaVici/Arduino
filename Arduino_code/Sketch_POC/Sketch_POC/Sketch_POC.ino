const int motors = 5;
const int tab[motors] = {6,7,8, 9, 10};

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

// Triggers every time something happens on the serial connection
// You write bytes by pairs to the serial communication: 
// [motor number, intensity (0-255)]
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

void loop() // run over and over
{
  
}
