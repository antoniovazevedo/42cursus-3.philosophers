SRCS	= 	srcs/main.c \
			srcs/validation.c \
			srcs/threads.c \
			srcs/forks.c \
			srcs/philos.c \
			srcs/actions.c

OBJS	= ${SRCS:.c=.o}
INCDIR	= includes
NAME	= philo
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror 
# -fsanitize=address -g
RM		= rm -f

all:	${NAME}

${NAME}: ${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

%.o:	%.c
		${CC} ${CFLAGS}  -c $< -o $@  -I ${INCDIR}

clean:
		${RM} ${OBJS}
		${RM} ${BONUS_OBJS}

fclean: clean
		${RM} ${NAME}

re:		fclean all

norm:	
		norminette includes/*.h
		norminette srcs/*.c

.PHONY: all clean fclean re norm
