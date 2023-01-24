_PHILO_ =		\
		philo_bonus.c ft_atoi.c ft_itoa.c ft_strjoin.c philo.c \
		philo_action.c philo_init.c philo_utils.c free_data.c\

FDF			= ${addprefix sources/, ${_PHILO_}}

OBJ = ${FDF:.c=.o}

DEP = ${OBJ:.o=.d}

NAME			= philo
INDIR			= include
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -MMD

all:	${NAME}

${NAME}:	${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean:
	${RM} ${DEP} ${OBJ}

fclean:		clean
	${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re

-include ${DEP}