/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:40:21 by dhubleur          #+#    #+#             */
/*   Updated: 2022/01/13 14:45:26 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_timestamp(t_philo *philo)
{
	long long int	elapsed;

	elapsed = get_time_in_ms() - philo->params->start_time;
	pthread_mutex_lock(&(philo->mutex->console));
	ft_putnbr(elapsed);
	if (elapsed < 10)
		ft_putstr("     #");
	else if (elapsed < 100)
		ft_putstr("    #");
	else if (elapsed < 1000)
		ft_putstr("   #");
	else if (elapsed < 10000)
		ft_putstr("  #");
	else
		ft_putstr(" #");
}

void	print_msg(t_philo *philo, char action)
{
	print_timestamp(philo);
	ft_putnbr(philo->position + 1);
	if (action == 'f')
		ft_putstr(" has taken a fork\n");
	if (action == 'e')
		ft_putstr(" is eating\n");
	if (action == 's')
		ft_putstr(" is sleeping\n");
	if (action == 't')
		ft_putstr(" is thinking\n");
	if (action == 'd')
		ft_putstr(" died\n");
	pthread_mutex_unlock(&(philo->mutex->console));
}
