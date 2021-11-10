# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 13:58:50 by ashea             #+#    #+#              #
#    Updated: 2021/01/18 14:41:58 by ashea            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three

SOURCE = main init free potok monitor utilities ft_atoi ft_itoa

RULE = $(addsuffix .c, $(addprefix ./, $(SOURCE)))

OBJ = $(RULE:.c=.o)

FLAGS = -Wall -Werror -Wextra -I.

all: $(NAME)

$(NAME):$(OBJ)
	gcc -o $(NAME) $(FLAGS) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re