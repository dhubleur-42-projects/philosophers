/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:04:50 by dhubleur          #+#    #+#             */
/*   Updated: 2022/01/13 14:05:10 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_tables(t_params *params, t_mutex *mutex)
{
	free(params->threads);
	free(params->philos);
	free(mutex->forks);
}

void	deinit_mutex(t_params *params, t_mutex *mutex)
{
	int		i;

	i = -1;
	while (++i < params->number_of_philos)
		pthread_mutex_destroy(&(mutex->forks[i]));
	pthread_mutex_destroy(&(mutex->console));
	pthread_mutex_destroy(&(mutex->ended));
	free_tables(params, mutex);
}

t_bool	init_forks_mutex(t_mutex *mutex, int number_of_philos)
{
	int		i;
	int		j;

	i = -1;
	while (++i < number_of_philos)
	{
		if (pthread_mutex_init(&(mutex->forks[i]), NULL) != 0)
		{
			j = -1;
			while (++j < i)
				pthread_mutex_destroy(&(mutex->forks[j]));
			return (FALSE);
		}
	}
	return (TRUE);
}

t_bool	init_mutex(t_mutex *mutex, int number_of_philos)
{
	int		i;
	t_bool	mutex_error;

	mutex_error = FALSE;
	mutex->forks = malloc(sizeof(pthread_mutex_t) * number_of_philos);
	if (!mutex->forks)
		return (FALSE);
	if (!init_forks_mutex(mutex, number_of_philos))
		return (FALSE);
	if (pthread_mutex_init(&(mutex->console), NULL) != 0)
		mutex_error = TRUE;
	if (!mutex_error && pthread_mutex_init(&(mutex->ended), NULL) != 0)
	{
		mutex_error = TRUE;
		pthread_mutex_destroy(&(mutex->console));
	}
	if (mutex_error)
	{
		i = -1;
		while (++i < number_of_philos)
			pthread_mutex_destroy(&(mutex->forks[i]));
		return (FALSE);
	}
	mutex->stop = FALSE;
	return (TRUE);
}
