#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

#include "Arduino.h"
#include "keys.h"

#define OPT_STRING	"hp:"
#define USAGE		"./arduino_serial -p <port>\n"

// Return values:
// 0: Go on with execution
// 1: Stop after this function returns
int	get_opts(int ac, char **av, Arduino *ard)
{
  int	c;
  while ((c = getopt(ac, av, OPT_STRING)) != -1)
    {
      switch (c)
	{
	case 'h':
	  printf(USAGE);
	  return 1;
	case 'p':
	  ard->fd = fopen(optarg, "w+");
	  if (!ard->fd)
	    {
	      fprintf(stderr, "Could not open %s\n", optarg);
	      return 1;
	    }
	  break ;
	default:
	  fprintf(stderr, "Unknown option: %c\n", c);
	  printf(USAGE);
	  return 1;
	}
    }
  return 0;
}

void	send_order(Arduino *a, int num, char mode)
{
  t_order	o;

  o.motor = num;
  o.mode = mode;
  fwrite(&o, sizeof(t_order), 1, a->fd);
  fflush(a->fd);
}

void	send_inputs(Arduino *a)
{
  const t_motor		tab[] = {{113, 97}};
  const unsigned	key_size = sizeof(tab) / sizeof(t_motor);
  int			c;

  // Set as raw so we don't have to type a newline
  system("/bin/stty raw");
  while ((c = getchar()) != EOF)
    {
      unsigned	i = 0;
      if (c == 27 || c == 4) // ESC or EOF
	break ;
      while (i < key_size)
	{
	  if (c == tab[i].on)
	    {
	      send_order(a, i, MODE_ON);
	      break ;
	    }
	  else if (c == tab[i].off)
	    {
	      send_order(a, i, MODE_OFF);
	      break ;
	    }
	  i++;
	}
      if (i == key_size)
	printf("\rUnsupported keypress: %d\n", c);
    }
  // Reset it as default
  system("/bin/stty cooked");
}

int	main(int ac, char **av)
{
  Arduino ard;

  init_arduino(&ard);
  if (!get_opts(ac, av, &ard))
    {
      if (!ard.fd)
	{
	  fprintf(stderr, "Please enter a port\n");
	}
      else
	{
	  puts("Waiting for Arduino...");
	  sleep(3);
	  puts("Arduino is ready!");
	  send_inputs(&ard);
	}
    }
  shutdown_arduino(&ard);
  return 0;
}
