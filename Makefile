# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 13:40:23 by idakhlao          #+#    #+#              #
#    Updated: 2024/11/15 17:14:52 by idakhlao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = prout.c utils.c
OBJS = ${SRCS:.c=.o}
CFLAGS = -Wall -Wextra -Werror -g3 
CC = cc
RM = rm -f

all : $(NAME) 

.c.o:
	cc $(CFLAGS) -c -o $@ $< 

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	${RM} ${OBJS}

fclean : clean
	${RM} ${NAME}

ac : all clean
	make clean

re : fclean all

.PHONY = make clean fclean re
