/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:16:47 by medric            #+#    #+#             */
/*   Updated: 2022/06/20 13:07:00 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	free_procss(t_data *data)
{
	if (data->pid)
		free(data->pid);
	if (data->thread)
		free(data->thread);
}

void	actions(t_data *data)
{
	while (data->must_num_eat != 0)
	{
		philo_eat(data);
		philo_sleep_thinking(data);
	}
	if (data->must_num_eat == 0 && data->num_eat != 0)
		delay(50);
	free_procss(data);
	exit(0);
}

int	pid_thread(t_data *data)
{
	data->pid = (pid_t *)malloc(sizeof(pid_t) * data->philo_num);
	if (!data->pid)
		return (ERROR);
	data->thread = (pthread_t *)malloc(sizeof(pthread_t) * data->philo_num);
	if (!data->pid)
		return (ERROR);
	return (SUCCESS);
}

int	start_philo(t_data *data, int i)
{
	sem_wait(data->killing_groups[data->id]);
	if (pthread_create(&data->thread[i], NULL, monitoring, data) != 0)
	{
		sem_wait(data->print);
		printf("Thread don't create\n");
		sem_post(data->print);
		return (ERROR);
	}
	pthread_detach(data->thread[i]);
	sem_post(data->killing_groups[data->id]);
	actions(data);
	return (SUCCESS);
}

int	work_philo(t_data *data)
{
	size_t	i;

	i = -1;
	if (pid_thread(data) == ERROR)
		return (ERROR);
	data->start_time = get_curr_time();
	data->last_eating_time = data->start_time;
	while (++i < (size_t) data->philo_num)
	{
		data->id = i;
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (ERROR);
		else if (data->pid[i] == 0)
		{
			if (start_philo(data, i) == ERROR)
				break ;
		}
	}
	if (!free_all(data))
		return (ERROR);
	return (SUCCESS);
}
