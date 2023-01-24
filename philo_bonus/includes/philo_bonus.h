/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 15:47:09 by medric            #+#    #+#             */
/*   Updated: 2022/06/20 12:45:53 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define ERROR 0
# define SUCCESS 1
# define FORKS "/forks_"
# define PRINT "/print_"
# define LAST "/last_eating_"
# define KILL "/killing_philo_"
# define DEATH 1
# define NOT_DIE 0
# define EAT_COMPLETE 1
# define EAT_NOT_COMPLETE 0
# define LOCK "/lock_"
# define DIE "/die_"

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

typedef struct s_data
{
	int				philo_num;
	long int		time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	long int		start_time;
	int				stop;
	char			**last;
	size_t			id;
	int				must_num_eat;
	int				num_eat;
	sem_t			*forks;
	sem_t			*print;
	int				die;
	sem_t			*lock;
	sem_t			**last_eating;
	sem_t			**killing_groups;
	long int		last_eating_time;
	pthread_t		*thread;
	char			**killing;
	pid_t			*pid;
}					t_data;

int			ft_atoi(const char *str);
char		*ft_itoa(int n);
void		init_data(t_data *args);
char		*ft_strjoin(char const *s1, char const *s2);
int			work_philo(t_data *data);
void		write_msg(char *s, t_data *philo);
long int	get_curr_time(void);
void		delay(unsigned int time);
void		*monitoring(void *arg);
void		philo_eat(t_data *data);
void		philo_sleep_thinking(t_data *data);
int			parse_arg1(int ac, char *av[], t_data *args);
int			parse_arg2(int ac, char *av[], t_data *args);
int			parse_arg_event(int ac, char *av[], t_data *args);
char		**create_names(char *name, int num_sem);
void		wait_proc(size_t i, size_t num_p);
void		killing_proc(pid_t *pid, size_t num, sem_t **killing_groups);
void		wait_philos(t_data *data);
void		free_proc(t_data *data);
int			free_all(t_data *data);
void		free_names(char **s, int num);
int			close_sem(sem_t **groups, size_t num);

#endif
