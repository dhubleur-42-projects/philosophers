/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:11:23 by dhubleur          #+#    #+#             */
/*   Updated: 2022/01/13 14:42:09 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

//Parsing
t_bool		is_integer(char *str);
int			ft_simple_atoi(char *str);

//Put functions
void		ft_putstr(char *str);
void		ft_putnbr(long long int nbr);

//Starter
void		start_philos(t_params *params);
void		setup_philo(t_params *params, t_philo *philo,
				t_mutex *mutex, t_bool wait);
t_bool		start_philo(t_params *params, t_mutex *mutex, int i, t_bool wait);
t_bool		start_even_philos(t_params *params, t_mutex *mutex);
t_bool		start_odd_philos(t_params *params, t_mutex *mutex);

//Routine
void		*routine(void	*param);
void		life_checker(t_params	*params);

//Util
long long	get_time_in_ms(void);
void		print_msg(t_philo *philo, char action);
void		free_tables(t_params *params, t_mutex *mutex);
void		deinit_mutex(t_params *params, t_mutex *mutex);
t_bool		init_forks_mutex(t_mutex *mutex, int number_of_philos);
t_bool		init_mutex(t_mutex *mutex, int number_of_philos);
void		end_program(t_params *params, t_mutex *mutex);

#endif