# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabsanto <sabsanto@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 19:21:14 by sabsanto          #+#    #+#              #
#    Updated: 2025/08/14 02:51:54 by sabsanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = philo
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread -O2
SRCS        = main.c utils.c routine.c init.c init_philos.c monitor.c validation.c
OBJS        = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "\033[1;32m✅ successful!"
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
