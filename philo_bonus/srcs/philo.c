/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:00:55 by dhubleur          #+#    #+#             */
/*   Updated: 2022/01/19 10:42:47 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_start_eat(t_philo *philo)
{
	if (philo->params->number_of_philos == 1)
	{
		print_msg(philo, 'f');
		usleep((philo->params->time_to_die + 10) * 1000);
	}
	sem_wait(philo->semaphores->forks);
	sem_wait(philo->access_eat);
	(philo->locked_forks)++;
	sem_post(philo->access_eat);
	print_msg(philo, 'f');
	sem_wait(philo->semaphores->forks);
	sem_wait(philo->access_eat);
	(philo->locked_forks)++;
	sem_post(philo->access_eat);
	print_msg(philo, 'f');
	print_msg(philo, 'e');
}

void	philo_eat(t_philo *philo)
{
	usleep(philo->params->time_to_eat * 1000);
	sem_wait(philo->access_eat);
	philo->last_eat = get_time_in_ms();
	(philo->total_eat)++;
	(philo->locked_forks) -= 2;
	sem_post(philo->access_eat);
	sem_post(philo->semaphores->forks);
	sem_post(philo->semaphores->forks);
}

void	routine(t_philo	*philo)
{
	pthread_t	thread;

	if (philo->wait)
		usleep(philo->params->time_to_eat * 1000);
	pthread_create(&thread, NULL, &life_checker, philo);
	pthread_detach(thread);
	while (TRUE)
	{
		philo_start_eat(philo);
		philo_eat(philo);
		print_msg(philo, 's');
		usleep(philo->params->time_to_sleep * 1000);
		print_msg(philo, 't');
	}
	exit(1);
}
