/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:22:18 by medric            #+#    #+#             */
/*   Updated: 2022/06/19 23:20:36 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_data(t_parse_arg *args)
{
	args->num_philo = 0;
	args->time_to_die = 0;
	args->time_to_eat = 0;
	args->time_to_sleep = 0;
	args->error = 0;
}

static void	init_utils_philo(t_philos *philo, int i,
								t_data *data, t_parse_arg *args)
{
	philo->finish_mutex = &data->finish_mutex;
	philo->print_mutex = &data->print_mutex;
	philo->eat_num_mutex = &data->eat_num_mutex[i];
	philo->start_time = data->start_time;
	philo->last_eating_time = data->start_time;
	philo->last_eating_num_mutex = &data->last_eating_num_mutex[i];
	philo->time_to_die = args->time_to_die;
	philo->time_to_eat = args->time_to_eat;
	philo->time_to_sleep = args->time_to_sleep;
}

/** @brief This function creat philosohper with base for him
 * @param i Number of philosopher
 * @param forks [0] or [1] this is fork eating thing for philo
 * */
static void	init_philos(t_data *data, t_parse_arg *args, int i)
{
	t_philos	*philo;

	philo = &data->philos[i];
	philo->finish = &data->finish;
	philo->print = &data->print;
	init_utils_philo(philo, i, data, args);
	philo->philos_id = (unsigned int)i;
	if (i < data->philo_num - 1)
	{
		philo->forks[0] = &data->forks[i];
		philo->forks[1] = &data->forks[(i + 1) % data->philo_num];
	}
	else
	{
		philo->forks[1] = &data->forks[i];
		philo->forks[0] = &data->forks[(i + 1) % data->philo_num];
	}
	philo->end_eat_num_mutex = &data->end_eat_num_mutex[i];
	philo->num_eat = args->num_eat;
	philo->check_eat = args->num_eat;
}

/** @brief This function create mas philo, which have some philo,
 * 	which have their information
 * @param  data prime struct
 * @param  args parse args
 * */
int	represnt_philosophers(t_data *data, t_parse_arg *args)
{
	ssize_t	i;

	i = -1;
	data->philos = (t_philos *)malloc(sizeof(t_philos) * data->philo_num);
	if (!data->philos)
		return (ERROR);
	memset(data->philos, 0, sizeof(t_philos) * data->philo_num);
	while (++i < data->philo_num)
		init_philos(data, args, i);
	return (SUCCESS);
}
