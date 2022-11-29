/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:39:44 by dhubleur          #+#    #+#             */
/*   Updated: 2022/01/13 15:24:55 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
}

void	ft_putnbr(long long int nbr)
{
	char		c;

	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10);
	}
	c = (nbr % 10) + '0';
	write(1, &c, 1);
}
