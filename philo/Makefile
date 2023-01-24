_PHILO_ =		\
		philo.c ft_atoui.c  init_philo.c init_philo_utils.c \
		philo_active.c philo_active_utils.c monitoring.c  free_data.c \

FDF			= ${addprefix sources/, ${_PHILO_}}

OBJ = ${FDF:.c=.o}

DEP = ${OBJ:.o=.d}

NAME			= philo
INDIR			= include
CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -MMD

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