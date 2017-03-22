NAME	= arduino_serial

CC	= gcc

CXXFLAGS += -Wall -Wextra
CXXFLAGS += -I./include/

SRCDIR = ./src/
OBJDIR = ./obj/

SRC	=	$(SRCDIR)main.c \
		$(SRCDIR)Arduino.c

OBJ	= $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CXXFLAGS)

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $@

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
