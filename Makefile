NAME = webserv

SRCS = ./main.cpp

OBJS = $(SRCS:.cpp=.o)

CPPFLAGS = -Wall -Werror -Wextra -std=c++98

%.o: %.cpp
	c++ -c $< $(CPPFLAGS) -o $@

$(NAME): $(OBJS)
	c++ $^ $(CPPFLAGS) -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
