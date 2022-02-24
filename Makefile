# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 11:30:49 by mdaillet          #+#    #+#              #
#    Updated: 2022/02/24 13:03:23 by mdaillet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COMPILER = c++
FLAGS = -Wall -Wextra -Werror -std=c++98 

NAME = Containers

SRCS = tests/main.cpp tests/ft_test.cpp tests/stl_test.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

%.o: %.cpp
	@echo "\033[0;33mCompiling..."
	$(COMPILER) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "Compiling..."
	${COMPILER} ${FLAGS} $(OBJS) -o $(NAME)
	@echo "\033[0m\033[0;32m"
	@echo "Compilation done ! Execute ./Containers to compare ft and stl."
	@echo "\033[0m"

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f *.txt


re: fclean all


test: re
	./$(NAME)


.PHONY: all clean fclean re test
