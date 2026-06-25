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

static int	check_death(pthread_mutex_t *lock, int *flag, int *stop)
{
	int	death;

	death = get_flag(lock, flag);
	if (death)
	{
		*stop = 1;
		return (1);
	}
	return (0);
}

static int	start_eating(pthread_mutex_t *first, pthread_mutex_t *second,
							t_philo *p, int *stop)
{
	pthread_mutex_lock(first);
	printf("%lld %d has taken a fork\n", get_time_ms(), p->num_philo + 1);
	if (check_death(p->death_lock, p->death_f, stop))
	{
		pthread_mutex_unlock(first);
		return (0);
	}
	pthread_mutex_lock(second);
	printf("%lld %d has taken a fork\n", get_time_ms(), p->num_philo + 1);
	if (check_death(p->death_lock, p->death_f, stop))
	{
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
		return (0);
	}
	printf("%lld %d is eating\n", get_time_ms(), p->num_philo + 1);
	usleep(p->rules->time_to_eat * 1000);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
	return (1);
}

static int	have_a_meal(t_philo *p, int *stop)
{
	int	left;
	int	right;

	left = p->num_philo;
	right = p->num_philo + 1;
	if (p->num_philo == p->rules->num_philos - 1)
		right = 0;
	if (check_death(p->death_lock, p->death_f, stop))
			return (0);
	if (p->num_philo % 2 == 0)
		return (start_eating(&(p->forks[left]), &(p->forks[right]), p, stop));
	else
		return (start_eating(&(p->forks[right]), &(p->forks[left]), p, stop));
	return (1);
}

static void	sync_philos(pthread_mutex_t *lock, int *flag)
{
	while (1)
	{
		if (get_flag(lock, flag) == 1)
			break ;
		usleep(10000);
	}
}

void	*philo_routine(void *args)
{
	t_philo		*p;
	int			meals_left;
	int			stop;

	p = (t_philo *)args;
	meals_left = p->rules->meals_to_eat;
	stop = 0;
	sync_philos(p->write_lock, p->start_f);
	while (!stop)
	{
		if (meals_left == 0)
		{
			toggle_flag(p->write_lock, &p->done_f);
			break;
		}
		if (check_death(p->death_lock, p->death_f, &stop))
			continue ;
		if (!have_a_meal(p, &stop))
			continue ;
		if (meals_left > 0)
			meals_left--;
		if (check_death(p->death_lock, p->death_f, &stop))
			continue ;
		printf("%lld %d is sleeping\n", get_time_ms(), p->num_philo + 1);
		usleep(p->rules->time_to_sleep * 1000);
	}
	return (NULL);
}
