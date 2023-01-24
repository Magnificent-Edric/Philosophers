/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 17:55:25 by medric            #+#    #+#             */
/*   Updated: 2022/05/30 22:52:47 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <stdio.h>

static int	check(long int n)
{
	if (n >= 0)
		return (1);
	else
		return (-1);
}

static int	len(long int n)
{
	size_t	len;

	len = 1;
	if (n < 0)
	{
		len = 2;
		n = n * (-1);
	}
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*putch(long int n, long int len, long int z)
{
	long int		i;
	char			*str;

	i = len;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return (NULL);
	i--;
	str[i + 1] = '\0';
	while (len > 0)
	{
		str[i] = '0' + z * (n % 10);
		n = (n / 10);
		i--;
		len--;
	}
	if (z < 0)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	long int			newn;
	long int			z;
	long int			l;
	char				*str;

	newn = n;
	z = check(newn);
	l = len(newn);
	str = putch(newn, l, z);
	return (str);
}
