/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:25:48 by dhubleur          #+#    #+#             */
/*   Updated: 2022/01/18 15:24:29 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_child(int exit_status, t_philo *philo)
{
	free_tables(philo->params);
	sem_close(philo->access_eat);
	sem_close(philo->semaphores->console);
	sem_close(philo->semaphores->forks);
	return (exit_status);
}

void	check_death(t_philo *philo)
{
	int	forks;

	if ((get_time_in_ms() - philo->last_eat) > philo->params->time_to_die)
	{
		forks = philo->locked_forks;
		sem_post(philo->access_eat);
		print_msg(philo, 'd');
		if (forks >= 1)
			sem_post(philo->semaphores->forks);
		if (forks == 2)
			sem_post(philo->semaphores->forks);
		exit(free_child(1, philo));
	}
}

void	*life_checker(void	*param)
{
	t_philo	*philo;
	int		forks;

	philo = (t_philo *) param;
	while (TRUE)
	{
		sem_wait(philo->access_eat);
		check_death(philo);
		if (philo->params->must_eat > 0
			&& philo->total_eat >= philo->params->must_eat)
		{
			forks = philo->locked_forks;
			sem_post(philo->access_eat);
			if (forks >= 1)
				sem_post(philo->semaphores->forks);
			if (forks == 2)
				sem_post(philo->semaphores->forks);
			exit(free_child(0, philo));
		}
		sem_post(philo->access_eat);
		usleep(1000);
	}
}
