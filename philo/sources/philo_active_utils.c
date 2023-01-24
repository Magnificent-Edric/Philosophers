/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_active_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:35:10 by medric            #+#    #+#             */
/*   Updated: 2022/06/20 13:26:05 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/** @brief This function work with eat,sleep and thinking
 *  in  eating we check last_eating_time
 *  in sleeping we unlock forks
 *  in thinking we check eat_number for every philo
 * */
void	philo_eat_sleep_thinking(t_philos *philo)
{
	write_msg("is eating", philo);
	pthread_mutex_unlock(philo->forks[1]);
	delay_philo(philo->time_to_eat);
	pthread_mutex_lock(philo->last_eating_num_mutex);
	philo->last_eating_time = get_curr_time();
	pthread_mutex_unlock(philo->last_eating_num_mutex);
	pthread_mutex_lock(philo->end_eat_num_mutex);
	if (philo->num_eat > 0)
		philo->num_eat--;
	pthread_mutex_unlock(philo->end_eat_num_mutex);
	write_msg("is sleeping", philo);
	pthread_mutex_unlock(philo->forks[0]);
	delay_philo(philo->time_to_sleep);
	write_msg("is thinking", philo);
}

/** @brief This function print msg and we lock/unlock print_mutex
 * */
void	write_msg(char *s, t_philos *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	if (*philo->print)
		printf("%ld %u %s\n", get_curr_time()
			- philo->start_time, philo->philos_id, s);
	pthread_mutex_unlock(philo->print_mutex);
}

/** @brief This function create delay for diffrent works
 * @param time  delay time
 * */
void	delay_philo(unsigned int time)
{
	long int	curr;

	curr = get_curr_time();
	while (get_curr_time() - curr < time)
		usleep(600);
}
