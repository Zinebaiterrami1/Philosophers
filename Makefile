NAME = philo
CC = cc 
CFLAGS = -Wall -Wextra -Werror

SOURCES = philo.c\
			philo_utils.c\
			utils.c

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