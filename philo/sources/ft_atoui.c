/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:13:37 by medric            #+#    #+#             */
/*   Updated: 2022/05/27 20:59:23 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isdigit(int n)
{
	return ((n >= 48 && n <= 57));
}

static int	check_space(const char *str)
{
	long long int	i;

	i = 0;
	while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
			|| str[i] == '\f' || str[i] == '\r') && str[i] != '\0')
		i++;
	return (i);
}

unsigned int	atoui(char **str, int *count)
{
	long unsigned int		t;

	t = 0;
	while (**str != '\0' && ft_isdigit(**str))
	{
		t = t * 10 + (**str - '0');
		(*str)++;
		(*count)++;
	}
	return (t);
}

unsigned int	ft_atoui(char *str, int *error)
{
	long unsigned int		t;
	int						count;
	int						i;

	t = 0;
	i = 0;
	count = 0;
	i = check_space(str);
	if (str[i] == '-')
	{
		*error = -1;
		return (ERROR);
	}
	else if (str[i] == '+')
		i++;
	t = atoui(&str, &count);
	if (count > 10 || t > UINT_MAX)
	{
		*error = -1;
		return (ERROR);
	}
	return (t);
}
