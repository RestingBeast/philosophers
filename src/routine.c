/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 20:00:58 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/08/12 16:03:41 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_eating(pthread_mutex_t *f, pthread_mutex_t *s, t_philo *p)
{
	pthread_mutex_lock(f);
	print_status(p, "has taken a fork");
	if (get_flag(p->death_lock, p->death_f))
	{
		pthread_mutex_unlock(f);
		return (0);
	}
	pthread_mutex_lock(s);
	print_status(p, "has taken a fork");
	if (get_flag(p->death_lock, p->death_f))
	{
		pthread_mutex_unlock(f);
		pthread_mutex_unlock(s);
		return (0);
	}
	update_death_timer(p);
	print_status(p, "is eating");
	usleep(p->rules->time_to_eat * 1000);
	pthread_mutex_unlock(f);
	pthread_mutex_unlock(s);
	return (1);
}

static int	have_a_meal(t_philo *p)
{
	int	left;
	int	right;

	left = p->num_philo;
	right = p->num_philo + 1;
	if (p->num_philo == p->rules->num_philos - 1)
		right = 0;
	if (get_flag(p->death_lock, p->death_f))
		return (0);
	if (p->num_philo % 2 == 0)
		return (start_eating(&(p->forks[left]), &(p->forks[right]), p));
	else
		return (start_eating(&(p->forks[right]), &(p->forks[left]), p));
}

static void	sync_philos(t_philo *p)
{
	while (1)
	{
		if (get_flag(p->write_lock, p->start_f) == 1)
			break ;
		usleep(10 * 1000);
	}
}

static int	is_done(t_philo *p)
{
	if (p->meals_left == 0)
	{
		toggle_flag(p->write_lock, &p->done_f);
		return (1);
	}
	return (0);
}

void	*philo_routine(void *args)
{
	t_philo		*p;

	p = (t_philo *)args;
	sync_philos(p);
	if (p->num_philo % 2 == 1)
		usleep(p->rules->time_to_eat * 1000);
	update_death_timer(p);
	while (1)
	{
		if (is_done(p))
			break ;
		if (get_flag(p->death_lock, p->death_f))
			break ;
		print_status(p, "is thinking");
		if (!have_a_meal(p))
			break ;
		if (p->meals_left > 0)
			p->meals_left--;
		if (get_flag(p->death_lock, p->death_f))
			break ;
		print_status(p, "is sleeping");
		usleep(p->rules->time_to_sleep * 1000);
	}
	return (NULL);
}
