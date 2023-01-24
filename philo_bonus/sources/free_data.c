/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 23:21:40 by medric            #+#    #+#             */
/*   Updated: 2022/06/20 12:46:11 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	free_names(char **s, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

int	close_sem(sem_t **groups, size_t num)
{
	size_t	i;

	i = -1;
	while (++i < num)
	{
		if (sem_close(groups[i]) == -1)
			return (ERROR);
	}
	free(groups);
	return (SUCCESS);
}

static void	free_name_data(t_data *data)
{
	if (data->killing)
		free_names(data->killing, data->philo_num);
	if (data->last)
		free_names(data->last, data->philo_num);
	if (data->pid)
		free(data->pid);
	if (data->thread)
		free(data->thread);
}

static int	free_all_next(t_data *data)
{
	if (data->forks && data->forks != SEM_FAILED)
	{
		if (sem_close(data->forks) == -1)
			return (ERROR);
	}
	if (data->lock && data->lock != SEM_FAILED)
	{
		if (sem_close(data->lock) == -1)
			return (ERROR);
	}
	if (data->killing_groups)
	{
		if (close_sem(data->killing_groups, data->philo_num) == ERROR)
			return (ERROR);
	}
	if (data->last_eating)
	{
		if (close_sem(data->last_eating, data->philo_num) == ERROR)
			return (ERROR);
	}
	free_name_data(data);
	return (SUCCESS);
}

int	free_all(t_data *data)
{
	size_t	i;
	int		exits;

	i = -1;
	while (++i < (size_t) data->philo_num)
	{
		if (waitpid(-1, &exits, 0) == -1)
			return (ERROR);
		if (exits >> 8 == EXIT_FAILURE)
		{
			killing_proc(data->pid, data->philo_num, data->killing_groups);
			break ;
		}
	}
	if (data->print && data->print != SEM_FAILED)
	{
		if (sem_close(data->print) == -1)
			return (ERROR);
	}
	if (free_all_next(data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
