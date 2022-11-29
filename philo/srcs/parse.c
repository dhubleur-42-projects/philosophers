/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:36:59 by dhubleur          #+#    #+#             */
/*   Updated: 2022/01/13 14:06:42 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_simple_atoi(char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		result *= 10;
		result += (str[i] - 48);
		i++;
	}
	return (result);
}

t_bool	is_numeric(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
	}
	return (TRUE);
}

t_bool	is_too_longer(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 10)
		return (TRUE);
	return (FALSE);
}

t_bool	is_overflowing(char *str)
{
	if (ft_simple_atoi(str) < 0)
		return (TRUE);
	return (FALSE);
}

t_bool	is_integer(char *str)
{
	if (!is_numeric(str))
		return (FALSE);
	if (is_too_longer(str))
		return (FALSE);
	if (is_overflowing(str))
		return (FALSE);
	return (TRUE);
}
