/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:30:16 by medric            #+#    #+#             */
/*   Updated: 2022/06/14 21:35:56 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/** @brief Get time of day with tv_sec and tv_usec
 * @return actual time of day for philo
*/
long int	get_curr_time(void)
{
	t_timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/** @brief Initsializing mutex finish and stop for destory
 * @param mutex This param initsializing
 * @param finish_stop param for destroy
 * */
int	init_mutex(t_mutex *mutex, bool *finish_stop)
{
	if (pthread_mutex_init(mutex, NULL))
		*finish_stop = true;
	else
		*finish_stop = false;
	if (*finish_stop == true)
		return (ERROR);
	return (SUCCESS);
}

/** @brief This function create mas mutex, which init_mutex for diffrent data
 * @param mutexs This mas had diffrent init_mutex data
 * @param philo_nb This is philosophers number
 * */
int	init_mutex_mas(t_mutex **mutexs, unsigned int philo_nb)
{
	bool	error;
	ssize_t	i;

	*mutexs = (t_mutex *)malloc(sizeof(t_mutex) * philo_nb);
	if (!(*mutexs))
		return (ERROR);
	i = -1;
	error = false;
	while (++i < philo_nb && !error)
	{
		if (pthread_mutex_init(&(*mutexs)[i], NULL))
			error = true;
	}
	if (error == true)
	{
		while (--i > -1)
			pthread_mutex_destroy(&(*mutexs)[i]);
		free(*mutexs);
		*mutexs = NULL;
		return (ERROR);
	}
	return (SUCCESS);
}

/** @brief This function create/init mutex and init philo
 * @param args data-base
 * @param data prime struct for philo
 * */
int	init_mutex_and_start(t_parse_arg *args, t_data *data)
{
	data->philo_num = args->num_philo;
	data->finish_stop = true;
	data->print_stop = true;
	data->print = true;
	data->start_time = get_curr_time();
	if (!init_mutex(&data->finish_mutex, &data->finish_stop)
		|| !init_mutex(&data->print_mutex, &data->print_stop))
		return (ERROR);
	if (!init_mutex_mas(&data->forks, data->philo_num)
		|| !init_mutex_mas(&data->eat_num_mutex, data->philo_num)
		|| !init_mutex_mas(&data->end_eat_num_mutex, data->philo_num)
		|| !init_mutex_mas(&data->last_eating_num_mutex, data->philo_num))
		return (ERROR);
	if (!represnt_philosophers(data, args)
		|| !monitoring_philo(data)
		|| !philo_start(data))
		return (ERROR);
	return (SUCCESS);
}

/** @brief Construction for init_philosophers
 * @param args data-base
 * @param data prime struct for philo
 */
int	init_philosphers(t_parse_arg *args, t_data *data)
{
	memset(data, 0, sizeof(*data));
	if (init_mutex_and_start(args, data))
		return (ERROR);
	return (SUCCESS);
}
