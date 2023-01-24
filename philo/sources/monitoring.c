/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 21:33:37 by medric            #+#    #+#             */
/*   Updated: 2022/06/20 13:23:02 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_philo_death(t_data *data, ssize_t i)
{
	long int	curr;

	curr = get_curr_time();
	pthread_mutex_lock(&data->last_eating_num_mutex[i]);
	if (curr - data->philos[i].last_eating_time > data->philos[i].time_to_die)
	{
		pthread_mutex_unlock(&data->last_eating_num_mutex[i]);
		pthread_mutex_lock(&data->finish_mutex);
		if (!data->finish)
		{
			data->finish = true;
			pthread_mutex_unlock(&data->finish_mutex);
			pthread_mutex_lock(&data->print_mutex);
			printf("%ld %ld died\n", curr - data->start_time, i);
			data->print = false;
			pthread_mutex_unlock(&data->print_mutex);
			return (DEATH);
		}
		pthread_mutex_unlock(&data->finish_mutex);
	}
	pthread_mutex_unlock(&data->philos->last_eating_num_mutex[i]);
	return (NOT_DIE);
}

static int	death_phil(t_data *data)
{
	ssize_t	i;
	int		end_eat;

	i = -1;
	end_eat = 0;
	while (++i < data->philo_num)
	{
		if (data->philos[i].check_eat > 0)
		{
			pthread_mutex_lock(&data->end_eat_num_mutex[i]);
			if (data->philos[i].num_eat == 0)
			{
				end_eat++;
				pthread_mutex_unlock(&data->end_eat_num_mutex[i]);
				continue ;
			}
			pthread_mutex_unlock(&data->end_eat_num_mutex[i]);
		}
		if (check_philo_death(data, i))
			return (DEATH);
	}
	if (end_eat == data->philo_num)
		return (DEATH);
	return (NOT_DIE);
}

static void	*monitoring(void *phil)
{
	t_data	*data;

	data = (t_data *)phil;
	while (1)
	{
		pthread_mutex_lock(&data->finish_mutex);
		if (data->finish)
		{
			pthread_mutex_unlock(&data->finish_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&data->finish_mutex);
		if (death_phil(data))
			return (NULL);
	}
}

int	monitoring_philo(t_data *data)
{
	if (pthread_create(&data->monitoring, NULL, monitoring, data))
	{
		pthread_mutex_lock(&data->finish_mutex);
		data->finish = true;
		pthread_mutex_unlock(&data->finish_mutex);
		return (ERROR);
	}
	return (SUCCESS);
}
