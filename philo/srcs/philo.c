/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:00:55 by dhubleur          #+#    #+#             */
/*   Updated: 2022/01/20 11:10:53 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	check_end(t_philo *philo)
{
	t_bool	result;

	pthread_mutex_lock(&(philo->mutex->ended));
	result = philo->mutex->stop;
	pthread_mutex_unlock(&(philo->mutex->ended));
	return (result);
}

t_bool	philo_start_eat(t_philo *philo, int fork1, int fork2)
{
	if (fork1 == fork2)
	{
		print_msg(philo, 'f');
		usleep(philo->params->time_to_die * 1000);
		return (TRUE);
	}
	pthread_mutex_lock(&(philo->mutex->forks[fork1]));
	if (check_end(philo))
	{
		pthread_mutex_unlock(&(philo->mutex->forks[fork1]));
		return (TRUE);
	}
	print_msg(philo, 'f');
	pthread_mutex_lock(&(philo->mutex->forks[fork2]));
	if (check_end(philo))
	{
		pthread_mutex_unlock(&(philo->mutex->forks[fork2]));
		pthread_mutex_unlock(&(philo->mutex->forks[fork1]));
		return (TRUE);
	}
	print_msg(philo, 'f');
	print_msg(philo, 'e');
	return (FALSE);
}

t_bool	philo_eat(t_philo *philo, int fork1, int fork2)
{
	usleep(philo->params->time_to_eat * 1000);
	if (check_end(philo))
	{
		pthread_mutex_unlock(&(philo->mutex->forks[fork2]));
		pthread_mutex_unlock(&(philo->mutex->forks[fork1]));
		return (TRUE);
	}
	pthread_mutex_lock(&(philo->access_eat));
	philo->last_eat = get_time_in_ms();
	(philo->total_eat)++;
	pthread_mutex_unlock(&(philo->access_eat));
	pthread_mutex_unlock(&(philo->mutex->forks[fork1]));
	pthread_mutex_unlock(&(philo->mutex->forks[fork2]));
	if (check_end(philo))
		return (TRUE);
	return (FALSE);
}

void	choose_forks(t_philo *philo, int *fork1, int *fork2)
{
	int	tmp_fork;

	*fork1 = philo->position;
	*fork2 = philo->position - 1;
	if (*fork2 < 0)
		*fork2 = philo->params->number_of_philos - 1;
	if (*fork1 < *fork2)
	{
		tmp_fork = *fork1;
		*fork1 = *fork2;
		*fork2 = tmp_fork;
	}	
}

void	*routine(void	*param)
{
	t_philo	*philo;
	int		fork1;
	int		fork2;

	philo = (t_philo *) param;
	choose_forks(philo, &fork1, &fork2);
	if (philo->wait)
		usleep(philo->params->time_to_eat * 1000);
	while (TRUE)
	{
		if (philo_start_eat(philo, fork1, fork2))
			return (NULL);
		if (philo_eat(philo, fork1, fork2))
			return (NULL);
		print_msg(philo, 's');
		usleep(philo->params->time_to_sleep * 1000);
		if (check_end(philo))
			return (NULL);
		print_msg(philo, 't');
	}
	return (NULL);
}
