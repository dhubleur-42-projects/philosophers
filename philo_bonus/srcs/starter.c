/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:02:36 by dhubleur          #+#    #+#             */
/*   Updated: 2022/01/18 15:10:43 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_philos(t_params *params)
{
	t_semaphores	semaphores;

	if (!init_semaphores(&semaphores, params->number_of_philos))
	{
		free_tables(params);
		return ;
	}
	params->start_time = get_time_in_ms();
	if (!start_even_philos(params, &semaphores))
	{
		deinit_semaphores(params, &semaphores);
		return ;
	}
	if (!start_odd_philos(params, &semaphores))
	{
		deinit_semaphores(params, &semaphores);
		return ;
	}
	end_program(params, &semaphores);
}

void	setup_philo(t_params *params, t_philo *philo,
			t_semaphores *semaphores, t_bool wait)
{
	philo->semaphores = semaphores;
	philo->params = params;
	philo->total_eat = 0;
	philo->last_eat = params->start_time;
	philo->wait = wait;
	philo->locked_forks = 0;
}

t_bool	start_philo(t_params *params, t_semaphores *semaphores,
	int i, t_bool wait)
{
	int			pid;
	t_philo		philo;
	char		name[128];

	philo.position = i;
	setup_philo(params, &philo, semaphores, wait);
	sem_unlink(philo_sem_name(i, name));
	philo.access_eat = sem_open(philo_sem_name(i, name), O_CREAT, S_IRWXU, 1);
	if (philo.access_eat == SEM_FAILED)
		return (FALSE);
	pid = fork();
	if (pid == -1)
		return (FALSE);
	if (pid == 0)
		routine(&philo);
	else
	{
		params->pids[i] = pid;
		params->philos[i] = philo.access_eat;
		return (TRUE);
	}
	return (TRUE);
}

t_bool	start_even_philos(t_params *params, t_semaphores *semaphores)
{
	int			i;

	i = 0;
	while (i < params->number_of_philos)
	{
		if (!start_philo(params, semaphores, i, FALSE))
			return (FALSE);
		i += 2;
	}
	return (TRUE);
}

t_bool	start_odd_philos(t_params *params, t_semaphores *semaphores)
{
	int			i;

	i = 1;
	while (i < params->number_of_philos)
	{
		if (!start_philo(params, semaphores, i, TRUE))
			return (FALSE);
		i += 2;
	}
	return (TRUE);
}
