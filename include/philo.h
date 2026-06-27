/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 19:47:52 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/05/23 19:47:53 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_rules		t_rules;
typedef struct s_philo		t_philo;
typedef struct s_data		t_data;

struct s_data
{
	t_rules						*rules;
	pthread_mutex_t 			*forks;
	t_philo						**philos;
	pthread_t					*threads;
	pthread_t					observer;
	int				start_f;
	int				death_f;
	pthread_mutex_t				death_lock;
	pthread_mutex_t				write_lock;
	pthread_mutex_t				print_lock;
};

struct s_rules
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals_to_eat;
};

struct s_philo
{
	int				num_philo;
	t_rules			*rules;
	pthread_mutex_t	*forks;
	int				*start_f;
	int				*death_f;
	int				done_f;
	pthread_mutex_t *write_lock;
	pthread_mutex_t *death_lock;
	pthread_mutex_t	*print_lock;
};

// data.c
int	init_data(int argc, char **argv, t_data *data);
void	clean_up(t_data *data);

// routine.c
void	*philo_routine(void *args);

// routine_utils.c
void		toggle_flag(pthread_mutex_t *lock, int *flag);
int			get_flag(pthread_mutex_t *lock, int *flag);
void		print_status(t_philo *p, const char *msg);

// observer.c
void	*observer_routine(void *args);

// utils.c
long long		get_time_ms(void);
int			is_integer(char *str);
int			simple_atoi(char *str);
int			fatal_error(char *msg);

// rules.c
t_rules		*init_rules(int argc, char **argv);

#endif
