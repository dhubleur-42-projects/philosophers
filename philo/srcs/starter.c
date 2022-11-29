/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:02:36 by dhubleur          #+#    #+#             */
/*   Updated: 2022/01/13 14:46:33 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_philos(t_params *params)
{
	t_mutex	mutex;

	if (!init_mutex(&mutex, params->number_of_philos))
	{
		free_tables(params, &mutex);
		return ;
	}
	params->start_time = get_time_in_ms();
	if (!start_even_philos(params, &mutex))
	{
		deinit_mutex(params, &mutex);
		return ;
	}
	if (!start_odd_philos(params, &mutex))
	{
		deinit_mutex(params, &mutex);
		return ;
	}
	life_checker(params);
	end_program(params, &mutex);
}

void	setup_philo(t_params *params, t_philo *philo,
			t_mutex *mutex, t_bool wait)
{
	philo->mutex = mutex;
	philo->params = params;
	philo->total_eat = 0;
	philo->last_eat = params->start_time;
	philo->wait = wait;
}

t_bool	start_philo(t_params *params, t_mutex *mutex, int i, t_bool wait)
{
	pthread_t	thread;
	t_philo		*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (FALSE);
	philo->position = i;
	setup_philo(params, philo, mutex, wait);
	if (pthread_mutex_init(&(philo->access_eat), NULL) != 0)
	{
		free(philo);
		return (FALSE);
	}
	if (pthread_create(&thread, NULL, &routine, philo) != 0)
	{
		pthread_mutex_destroy(&(philo->access_eat));
		free(philo);
		return (FALSE);
	}
	params->threads[i] = thread;
	params->philos[i] = philo;
	return (TRUE);
}

t_bool	start_even_philos(t_params *params, t_mutex *mutex)
{
	int			i;

	i = 0;
	while (i < params->number_of_philos)
	{
		if (!start_philo(params, mutex, i, FALSE))
			return (FALSE);
		i += 2;
	}
	return (TRUE);
}

t_bool	start_odd_philos(t_params *params, t_mutex *mutex)
{
	int			i;

	i = 1;
	while (i < params->number_of_philos)
	{
		if (!start_philo(params, mutex, i, TRUE))
			return (FALSE);
		i += 2;
	}
	return (TRUE);
}
