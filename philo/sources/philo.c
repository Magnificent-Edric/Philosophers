/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:45:41 by medric            #+#    #+#             */
/*   Updated: 2022/06/19 23:20:18 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	parse_arg1(int ac, char *av[], t_parse_arg *args)
{
	if (ac == 5)
	{
		args->num_philo = ft_atoui(av[1], &args->error);
		args->time_to_die = ft_atoui(av[2], &args->error);
		args->time_to_eat = ft_atoui(av[3], &args->error);
		args->time_to_sleep = ft_atoui(av[4], &args->error);
		args->num_eat = 0;
		if (args->error == -1)
			return (ERROR);
	}
	return (SUCCESS);
}

int	parse_arg2(int ac, char *av[], t_parse_arg *args)
{
	if (ac == 6)
	{
		args->num_philo = ft_atoui(av[1], &args->error);
		args->time_to_die = ft_atoui(av[2], &args->error);
		args->time_to_eat = ft_atoui(av[3], &args->error);
		args->time_to_sleep = ft_atoui(av[4], &args->error);
		args->num_eat = ft_atoui(av[5], &args->error);
		if (args->error == -1)
			return (ERROR);
	}
	return (SUCCESS);
}

int	parse_arg_event(int ac, char *av[], t_parse_arg *args)
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

void	wait_philos(t_data *data)
{
	unsigned int	i;

	i = -1;
	while (++i < (unsigned int) data->philo_num)
		pthread_join(data->philos[i].thread_id, NULL);
	pthread_join(data->monitoring, NULL);
}

int	main(int ac, char *av[])
{
	t_data		data;
	t_parse_arg	args;

	if (parse_arg_event(ac, av, &args) == ERROR)
	{
		write(1, "Invalid argumets\n", 18);
		return (0);
	}
	if (init_philosphers(&args, &data))
	{
		wait_philos(&data);
		free_data(&data);
		return (0);
	}
	wait_philos(&data);
	free_data(&data);
	return (0);
}
