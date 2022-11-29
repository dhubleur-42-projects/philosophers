/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:25:48 by dhubleur          #+#    #+#             */
/*   Updated: 2022/01/13 14:34:43 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	check_death(t_params *params, t_philo *philo)
{
	if ((get_time_in_ms() - philo->last_eat) > params->time_to_die)
	{
		pthread_mutex_unlock(&(philo->access_eat));
		print_msg(philo, 'd');
		pthread_mutex_lock(&(philo->mutex->ended));
		philo->mutex->stop = TRUE;
		pthread_mutex_unlock(&(philo->mutex->ended));
		return (TRUE);
	}
	return (FALSE);
}

t_bool	check_eat(t_params *params, t_bool all_finished, t_mutex *mutex)
{
	if (params->must_eat > 0 && all_finished)
	{
		pthread_mutex_lock(&(mutex->ended));
		mutex->stop = TRUE;
		pthread_mutex_unlock(&(mutex->ended));
		return (TRUE);
	}
	return (FALSE);
}

void	life_checker(t_params	*params)
{
	t_bool		all_finished;
	t_mutex		*mutex;
	t_philo		*philo;
	int			i;

	while (TRUE)
	{
		all_finished = TRUE;
		i = -1;
		while (++i < params->number_of_philos)
		{
			philo = params->philos[i];
			mutex = philo->mutex;
			pthread_mutex_lock(&(philo->access_eat));
			if (check_death(params, philo))
				return ;
			if (philo->total_eat < params->must_eat)
				all_finished = FALSE;
			pthread_mutex_unlock(&(philo->access_eat));
		}
		if (check_eat(params, all_finished, mutex))
			return ;
		usleep(5 * 1000);
	}
}
