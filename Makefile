SRCS			= main.cpp
OBJS			= $(SRCS:.cpp=.o)

RM				= rm -f
FLAGS			= c++ -g -Wall -Wextra -Werror -std=c++98 -fsanitize=address -I.

NAME			= ft_containers

all:			$(NAME)

.cpp.o:
				$(FLAGS) -o $@ -c $<

$(NAME):		$(OBJS)
				$(FLAGS) -o $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
