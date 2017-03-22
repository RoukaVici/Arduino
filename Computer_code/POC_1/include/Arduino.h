#ifndef ARDUINO_H_
# define ARUINO_H_

#include <stdio.h>

typedef struct	arduino
{
  FILE		*fd;
  unsigned	baudrate;
}		Arduino;

void	shutdown_arduino(Arduino *ard);
void	init_arduino(Arduino *ard);

#endif
