/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 00:00:58 by medric            #+#    #+#             */
/*   Updated: 2022/06/19 23:08:37 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	free_procs(t_data *data)
{
	if (data->pid)
		free(data->pid);
	if (data->thread)
		free(data->thread);
}

static int	monitor(t_data *data)
{
	sem_wait(data->lock);
	if (data->must_num_eat == 0 && data->num_eat != 0)
	{
		sem_post(data->lock);
		return (ERROR);
	}
	sem_post(data->lock);
	return (SUCCESS);
}

void	*monitoring(void *arg)
{
	t_data		*data;
	long int	curr;

	data = (t_data *)arg;
	if (monitor(data) == ERROR)
		return (NULL);
	while (1)
	{
		sem_wait(data->last_eating[data->id]);
		curr = get_curr_time();
		if (curr - data->last_eating_time > data->time_to_die)
		{
			sem_wait(data->print);
			printf("%ld %ld died\n", curr - data->last_eating_time, data->id);
			sem_post(data->last_eating[data->id]);
			free_procs(data);
			exit(EXIT_FAILURE);
		}
		sem_post(data->last_eating[data->id]);
		usleep(1000);
	}
	return (NULL);
}

void	philo_eat(t_data *data)
{
	sem_wait(data->forks);
	write_msg("has taken fork", data);
	sem_wait(data->forks);
	write_msg("has taken fork", data);
	sem_wait(data->last_eating[data->id]);
	data->last_eating_time = get_curr_time();
	sem_post(data->last_eating[data->id]);
	write_msg("is eating", data);
	delay(data->time_to_eat);
}

void	philo_sleep_thinking(t_data *data)
{
	sem_post(data->forks);
	sem_post(data->forks);
	write_msg("is sleeping", data);
	delay(data->time_to_sleep);
	write_msg("is thinking", data);
	sem_wait(data->lock);
	if (data->must_num_eat > 0)
		data->must_num_eat--;
	sem_post(data->lock);
}
