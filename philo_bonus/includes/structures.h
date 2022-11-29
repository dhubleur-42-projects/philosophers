/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:10:39 by dhubleur          #+#    #+#             */
/*   Updated: 2022/01/18 15:16:51 by dhubleur         ###   ########.fr       */
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
	int				*pids;
	sem_t			**philos;
}	t_params;

typedef struct s_semaphores
{
	sem_t	*forks;
	sem_t	*console;
}	t_semaphores;

typedef struct s_philo
{
	int				position;
	t_semaphores	*semaphores;
	t_params		*params;
	long long		last_eat;
	int				total_eat;
	t_bool			wait;
	sem_t			*access_eat;
	int				locked_forks;
}	t_philo;

#endif