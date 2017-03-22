#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "Arduino.h"

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

void	send(Arduino *a, const char *str)
{
  fwrite(str, 1, 1, a->fd);
  fflush(a->fd);
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
	  sleep(3);
	  char c = 2;
	  send(&ard, &c);
	  c = 1;
	  send(&ard, &c);
	}
    }
  shutdown_arduino(&ard);
  return 0;
}
