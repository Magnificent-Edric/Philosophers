/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:39:32 by medric            #+#    #+#             */
/*   Updated: 2022/06/01 23:06:51 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/time.h>

# define ERROR 0
# define SUCCESS 1
# define DEATH 1
# define NOT_DIE 0
# define EAT_COMPLETE 1
# define EAT_NOT_COMPLETE 0

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

typedef struct s_parse_arg
{
	unsigned int	num_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	long int		num_eat;
	int				error;
}					t_parse_arg;

typedef struct s_philos
{
	t_mutex			*finish_mutex;
	bool			*finish;
	t_mutex			*print_mutex;
	bool			*print;
	t_mutex			*eat_num_mutex;
	t_mutex			*end_eat_num_mutex;
	t_mutex			*forks[2];
	t_mutex			*last_eating_num_mutex;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	philos_id;
	long int		start_time;
	long int		last_eating_time;
	long int		num_eat;
	long int		check_eat;
	pthread_t		thread_id;
}					t_philos;

typedef struct s_data
{
	int			philo_num;
	long int	start_time;
	bool		finish_stop;
	bool		print_stop;
	bool		finish;
	bool		print;
	t_mutex		finish_mutex;
	t_mutex		print_mutex;
	t_mutex		*eat_num_mutex;
	t_mutex		*end_eat_num_mutex;
	t_mutex		*last_eating_num_mutex;
	t_mutex		*forks;
	t_philos	*philos;
	pthread_t	monitoring;
}		t_data;

unsigned int	ft_atoui(char *str, int *error);
int				parse_arg_event(int ac, char *av[], t_parse_arg *args);
long int		get_curr_time(void);
int				init_philosphers(t_parse_arg *args, t_data *data);
int				represnt_philosophers(t_data *data, t_parse_arg *args);
void			delay_philo(unsigned int time);
void			write_msg(char *s, t_philos *philo);
void			free_mutex(t_mutex **mutex, unsigned int num);
void			free_data(t_data *data);
int				philo_start(t_data *data);
int				monitoring_philo(t_data *data);
void			philo_eat_sleep_thinking(t_philos *philo);
void			init_data(t_parse_arg *args);

#endif