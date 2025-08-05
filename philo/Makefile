NAME = philo
CC = cc 
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread

SOURCES = philo.c\
			utils.c\
			monitor.c \
			routines.c\
			init.c\
			utils1.c

OBJECTS = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
		$(CC) $(CFLAGS) $(SOURCES) -o $(NAME)

clean :
		rm -rf $(OBJECTS)
fclean : clean
		rm -rf $(NAME)
re : clean fclean all

.PHONY : all clean fclean re

.SECONDARY : $(OBJECTS)