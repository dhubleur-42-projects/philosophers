/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:10:39 by dhubleur          #+#    #+#             */
/*   Updated: 2022/01/13 14:46:42 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

typedef struct s_params
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long long		start_time;
	pthread_t		*threads;
	struct s_philo	**philos;
}	t_params;

typedef struct s_mutex
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	console;
	pthread_mutex_t	ended;
	t_bool			stop;
}	t_mutex;

typedef struct s_philo
{
	int				position;
	t_mutex			*mutex;
	t_params		*params;
	long long		last_eat;
	int				total_eat;
	t_bool			wait;
	pthread_mutex_t	access_eat;
}	t_philo;

#endif