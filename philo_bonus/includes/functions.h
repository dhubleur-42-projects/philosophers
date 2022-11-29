/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:11:23 by dhubleur          #+#    #+#             */
/*   Updated: 2022/01/18 14:45:43 by dhubleur         ###   ########.fr       */
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
t_bool		start_philo(t_params *params, t_semaphores *semaphores,
				int i, t_bool wait);
t_bool		start_even_philos(t_params *params, t_semaphores *semaphores);
t_bool		start_odd_philos(t_params *params, t_semaphores *semaphores);

//Routine
void		routine(t_philo	*philo);
void		*life_checker(void	*param);

//Util
long long	get_time_in_ms(void);
void		print_msg(t_philo *philo, char action);
void		free_tables(t_params *params);
void		deinit_semaphores(t_params *params, t_semaphores *semaphores);
t_bool		init_semaphores(t_semaphores *semaphores, int number_of_philos);
void		end_program(t_params *params, t_semaphores *semaphores);
const char	*philo_sem_name(int pos, char *name);

#endif