#ifndef KEYS_H_
# define KEYS_H_

# define MODE_ON	1
# define MODE_OFF	0

// This structure represents a single motor.
// We define two keycodes: one for turning the motor on and one for turning it off.
typedef struct	s_motor
{
  int		on;
  int		off;
}		t_motor;

// The structure we send to the Arduino
typedef struct	s_order
{
  unsigned char		motor; // Motor number
  unsigned char		mode; // On or off
}		t_order;

#endif
