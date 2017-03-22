#include "Arduino.h"

void	init_arduino(Arduino *ard)
{
  ard->fd = NULL;
  ard->baudrate = 9600;
}

void	shutdown_arduino(Arduino *ard)
{
  if (ard->fd)
    fclose(ard->fd);
}
