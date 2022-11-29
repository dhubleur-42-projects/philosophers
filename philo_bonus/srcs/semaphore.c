/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:04:50 by dhubleur          #+#    #+#             */
/*   Updated: 2022/01/18 14:45:26 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

const char	*philo_sem_name(int pos, char *name)
{
	int		i;

	name[0] = 'e';
	name[1] = 'a';
	name[2] = 't';
	i = 3;
	while (pos >= 10)
	{
		name[i++] = (pos % 10) + '0';
		pos /= 10;
	}
	name[i] = '\0';
	return (name);
}

void	free_tables(t_params *params)
{
	free(params->pids);
	free(params->philos);
}

void	deinit_semaphores(t_params *params, t_semaphores *semaphores)
{
	sem_close(semaphores->forks);
	sem_unlink("global_forks");
	sem_close(semaphores->console);
	sem_unlink("global_console");
	free_tables(params);
}

t_bool	init_semaphores(t_semaphores *semaphores, int number_of_philos)
{
	sem_unlink("global_forks");
	sem_unlink("global_console");
	semaphores->forks = sem_open("global_forks",
			O_CREAT, S_IRWXU, number_of_philos);
	if (semaphores->forks == SEM_FAILED)
		return (FALSE);
	semaphores->console = sem_open("global_console", O_CREAT, S_IRWXU, 1);
	if (semaphores->console == SEM_FAILED)
	{
		sem_close(semaphores->forks);
		sem_unlink("global_forks");
		return (FALSE);
	}
	return (TRUE);
}
