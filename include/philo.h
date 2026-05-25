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

typedef struct s_routine	t_routine;
typedef struct s_philo		t_philo;
typedef struct s_data		t_data;

struct s_data
{
	int				num_philos;
	t_routine		*routine;
	pthread_mutex_t *forks;
	t_philo			**philosophers;
};

struct s_routine
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals_to_eat;
};

struct s_philo
{
	int				num_philo;
	t_routine		*routine;
	pthread_mutex_t	*forks;
};

// data.c
int	init_data(int argc, char **argv, t_data *data);
void	clean_up(t_data *data);

// routine.c
t_routine	*init_routine(int argc, char **argv);

// utils.c
long int	get_time_ms(void);
int			is_integer(char *str);
int			simple_atoi(char *str);
int			fatal_error(char *msg);

#endif
