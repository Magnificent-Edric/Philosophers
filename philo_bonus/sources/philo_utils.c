/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 00:02:38 by medric            #+#    #+#             */
/*   Updated: 2022/06/19 23:05:39 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	write_msg(char *s, t_data *philo)
{
	sem_wait(philo->print);
	if (philo->print)
		printf("%ld %lu %s\n", get_curr_time()
			- philo->start_time, philo->id, s);
	sem_post(philo->print);
}

/** @brief This function create delay for diffrent works
 * @param time  delay time
 * */
void	delay(unsigned int time)
{
	long int	curr;

	curr = get_curr_time();
	while (get_curr_time() - curr < time)
		usleep(600);
}

void	killing_proc(pid_t *pid, size_t num, sem_t **killing_groups)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		sem_wait(killing_groups[i]);
		kill(pid[i], SIGKILL);
		sem_post(killing_groups[i]);
		i++;
	}
}
