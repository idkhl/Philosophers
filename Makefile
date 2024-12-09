# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 13:40:23 by idakhlao          #+#    #+#              #
#    Updated: 2024/12/09 18:01:17 by idakhlao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = 	src/main.c src/actions.c src/routine.c src/utils.c
	
OBJS_DIR = .objects
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

CFLAGS = -Wall -Wextra -Werror -g3 -pthread
CC = cc
RM = rm -f

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR) $(OBJS_DIR)/src

all: $(NAME)

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)
	find $(OBJS_DIR) -type f -name "*.o" -delete

fclean: clean
	$(RM) $(NAME)


ac: all clean
	make clean

re: fclean all

.PHONY: all clean fclean re
