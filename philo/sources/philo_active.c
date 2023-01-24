/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_active.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 23:37:32 by medric            #+#    #+#             */
/*   Updated: 2022/06/19 23:20:59 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_get_forks(t_philos *philo, unsigned int fork_num)
{
	pthread_mutex_lock(philo->forks[fork_num]);
	write_msg("has taken fork", philo);
	if (philo->forks[0] == philo->forks[1])
	{
		delay_philo(philo->time_to_die + 1);
		pthread_mutex_unlock(philo->forks[fork_num]);
	}
}

static void	*philosopher(void *arg)
{
	t_philos	*args;

	args = (t_philos *)arg;
	while (1)
	{
		pthread_mutex_lock(args->finish_mutex);
		if (*args->finish)
		{
			pthread_mutex_unlock(args->finish_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(args->finish_mutex);
		if (args->num_eat <= 0 && args->check_eat > 0)
			return (NULL);
		philo_get_forks(args, 0);
		philo_get_forks(args, 1);
		philo_eat_sleep_thinking(args);
	}
}

/** @brief This function inisializing group philo and lock/unlock
 * */
static int	create_philo_work(unsigned int first,
							unsigned int step, t_data *data)
{
	while (first < (unsigned int) data->philo_num)
	{
		data->philos[first].thread_id = first;
		if (pthread_create(&data->philos[first].thread_id, NULL,
				philosopher, &data->philos[first]))
		{
			pthread_mutex_lock(&data->finish_mutex);
			data->finish = true;
			pthread_mutex_unlock(&data->finish_mutex);
			return (ERROR);
		}
		first += step;
	}
	return (SUCCESS);
}

/** @brief This function create two groups, which create two active work
 * @param 0 Inisializing first group with step  2
 * */
int	philo_start(t_data *data)
{
	if (data->philo_num == 2 && data->philos[0].time_to_eat < 10
		&& data->philos[0].time_to_die < 10
		&& data->philos[0].time_to_sleep < 10)
	{
		if (!create_philo_work(0, 2, data))
			return (ERROR);
		usleep(300);
		if (!create_philo_work(1, 2, data))
			return (ERROR);
		return (SUCCESS);
	}
	if (!create_philo_work(0, 2, data))
		return (ERROR);
	usleep(5000);
	if (!create_philo_work(1, 2, data))
		return (ERROR);
	return (SUCCESS);
}
