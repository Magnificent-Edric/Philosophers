/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 00:03:43 by medric            #+#    #+#             */
/*   Updated: 2022/06/19 23:11:24 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	init_data(t_data *args)
{
	args->philo_num = 0;
	args->time_to_die = 0;
	args->time_to_eat = 0;
	args->time_to_sleep = 0;
	args->id = 0;
}

int	parse_arg1(int ac, char *av[], t_data *args)
{
	if (ac == 5)
	{
		args->philo_num = ft_atoi(av[1]);
		args->time_to_die = ft_atoi(av[2]);
		args->time_to_eat = ft_atoi(av[3]);
		args->time_to_sleep = ft_atoi(av[4]);
		args->must_num_eat = -1;
		if (args->philo_num <= 0 || args->time_to_sleep <= 0
			|| args->time_to_die <= 0 || args->time_to_eat <= 0)
			return (ERROR);
	}
	return (SUCCESS);
}

int	parse_arg2(int ac, char *av[], t_data *args)
{
	if (ac == 6)
	{
		args->philo_num = ft_atoi(av[1]);
		args->time_to_die = ft_atoi(av[2]);
		args->time_to_eat = ft_atoi(av[3]);
		args->time_to_sleep = ft_atoi(av[4]);
		args->must_num_eat = ft_atoi(av[5]);
		args->num_eat = args->must_num_eat;
		if (args->philo_num <= 0 || args->must_num_eat <= 0
			|| args->time_to_die <= 0 || args->time_to_eat <= 0
			|| args->time_to_sleep <= 0)
			return (ERROR);
	}
	return (SUCCESS);
}

int	parse_arg_event(int ac, char *av[], t_data *args)
{
	if (ac > 6 || ac < 5)
		return (ERROR);
	init_data(args);
	if (ac == 5 && parse_arg1(ac, av, args))
		return (SUCCESS);
	if (ac == 6 && parse_arg2(ac, av, args))
		return (SUCCESS);
	return (ERROR);
}

char	**create_names(char *name, int num_sem)
{
	char	**names;
	char	*str;
	size_t	i;

	names = (char **)malloc(sizeof(char *) * num_sem);
	if (!names)
		return (NULL);
	i = 0;
	while (i < (size_t) num_sem)
	{
		str = ft_itoa(i);
		names[i] = ft_strjoin(name, str);
		free(str);
		i++;
	}
	return (names);
}
