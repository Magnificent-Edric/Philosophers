/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:15:10 by medric            #+#    #+#             */
/*   Updated: 2022/06/19 23:06:39 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

long int	get_curr_time(void)
{
	t_timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

sem_t	**init_sem_data(size_t num_sem, char **names)
{
	sem_t	**groups;
	size_t	i;

	i = -1;
	groups = (sem_t **)malloc(sizeof(sem_t *) * num_sem);
	if (!groups)
		return (NULL);
	if (!names)
		return (NULL);
	while (++i < num_sem)
	{
		groups[i] = sem_open(names[i], O_CREAT, 0666, 1);
		sem_unlink(names[i]);
	}
	return (groups);
}

int	init_work_data(t_data *data)
{
	data->last_eating = init_sem_data(data->philo_num, data->last);
	if (!data->last_eating)
		return (ERROR);
	data->killing_groups = init_sem_data(data->philo_num, data->killing);
	if (!data->killing_groups)
		return (ERROR);
	data->forks = sem_open(FORKS, O_CREAT, 0666, data->philo_num);
	if (data->forks == SEM_FAILED)
		return (ERROR);
	sem_unlink(FORKS);
	data->print = sem_open(PRINT, O_CREAT, 0666, 1);
	if (data->print == SEM_FAILED)
		return (ERROR);
	sem_unlink(PRINT);
	data->lock = sem_open(LOCK, O_CREAT, 0666, 1);
	if (data->lock == SEM_FAILED)
		return (ERROR);
	sem_unlink(LOCK);
	return (SUCCESS);
}

int	main(int ac, char *av[])
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (parse_arg_event(ac, av, &data) == ERROR)
	{
		write(1, "Invalid arguments\n", 18);
		return (0);
	}
	data.last = create_names(LAST, data.philo_num);
	data.killing = create_names(KILL, data.philo_num);
	if (!init_work_data(&data))
	{
		free_all(&data);
		return (0);
	}
	if (work_philo(&data) == ERROR)
	{
		free_all(&data);
		return (0);
	}
	return (0);
}
