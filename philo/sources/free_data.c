/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:57:34 by medric            #+#    #+#             */
/*   Updated: 2022/06/01 17:35:00 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_mutex(t_mutex **mutex, unsigned int num)
{
	ssize_t	i;

	i = -1;
	while (++i < num)
		pthread_mutex_destroy(&(*mutex)[i]);
	free(*mutex);
	*mutex = NULL;
}

void	free_data(t_data *data)
{
	if (!data->finish_stop)
		pthread_mutex_destroy(&data->finish_mutex);
	if (!data->print_stop)
		pthread_mutex_destroy(&data->print_mutex);
	free_mutex(&data->forks, data->philo_num);
	free_mutex(&data->eat_num_mutex, data->philo_num);
	free_mutex(&data->end_eat_num_mutex, data->philo_num);
	free_mutex(&data->last_eating_num_mutex, data->philo_num);
	free(data->philos);
	data->philos = NULL;
}
