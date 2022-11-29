/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:12:59 by dhubleur          #+#    #+#             */
/*   Updated: 2022/01/20 11:07:38 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_in_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	end_program(t_params *params, t_mutex *mutex)
{
	int		i;

	i = -1;
	while (++i < params->number_of_philos)
		pthread_join(params->threads[i], NULL);
	i = -1;
	while (++i < params->number_of_philos)
		pthread_mutex_destroy(&(mutex->forks[i]));
	free(mutex->forks);
	pthread_mutex_destroy(&(mutex->console));
	pthread_mutex_destroy(&(mutex->ended));
	i = -1;
	while (++i < params->number_of_philos)
		free(params->philos[i]);
	free(params->philos);
	free(params->threads);
}

t_bool	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf(ARG_ERROR);
		return (FALSE);
	}
	i = 0;
	while (++i < argc)
	{
		if (!is_integer(argv[i]))
		{
			printf(INTEGER_ERROR, i);
			return (FALSE);
		}
	}
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_params	params;

	if (!check_args(argc, argv))
		return (1);
	params.number_of_philos = ft_simple_atoi(argv[1]);
	params.time_to_die = ft_simple_atoi(argv[2]);
	params.time_to_eat = ft_simple_atoi(argv[3]);
	params.time_to_sleep = ft_simple_atoi(argv[4]);
	params.threads = malloc(sizeof(pthread_t) * params.number_of_philos);
	params.philos = malloc(sizeof(t_philo *) * params.number_of_philos);
	if (!params.threads || !params.philos)
	{
		free(params.threads);
		free(params.philos);
		return (1);
	}
	if (argc == 6)
		params.must_eat = ft_simple_atoi(argv[5]);
	else
		params.must_eat = -1;
	start_philos(&params);
}
