/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 20:00:58 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/05/23 20:00:59 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// To-do: Handle error in mutex locking later
static int	grab_forks(pthread_mutex_t *first, pthread_mutex_t *second, t_philo *p)
{
	pthread_mutex_lock(first);
	printf("%lld %d has taken a fork\n", get_time_ms(), p->num_philo + 1);
	pthread_mutex_lock(second);
	printf("%lld %d has taken a fork\n", get_time_ms(), p->num_philo + 1);
	printf("%lld %d is eating\n", get_time_ms(), p->num_philo + 1);
	usleep(p->rules->time_to_eat * 1000);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);

	return (0);
}

static int	have_a_meal(t_philo *p)
{
	int	left;
	int	right;

	left = p->num_philo;
	right = p->num_philo + 1;
	if (p->num_philo == p->rules->num_philos - 1)
		right = 0;
	if (p->num_philo % 2 == 0)
		grab_forks(&(p->forks[left]), &(p->forks[right]), p);
	else
		grab_forks(&(p->forks[right]), &(p->forks[left]), p);
	return (0);
}

void	*philo_routine(void *args)
{
	t_philo		*philo;
	int			meals_eaten;

	philo = (t_philo *)args;
	meals_eaten = philo->rules->meals_to_eat;
	while (1)
	{
		if (*(philo->start_f) == 0)
		{
			usleep(10000);
			continue ;
		}
		if (meals_eaten == 0)
		{
			philo->done_f = 1;
			break;
		}
		have_a_meal(philo);
		if (meals_eaten > 0)
			meals_eaten--;
		printf("%lld %d is sleeping\n", get_time_ms(), philo->num_philo + 1);
		usleep(philo->rules->time_to_sleep * 1000);
	}
	return (NULL);
}
