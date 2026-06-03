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

static int	check_for_death(t_philo *philo, long long time_to_die)
{
	usleep(10);
	if (*(philo->someone_died))
		return (1);
	if (get_time_ms() > time_to_die)
	{
		*(philo->someone_died) = 1;
		printf("%lld %d died\n", get_time_ms(), philo->num_philo + 1);
		return (1);
	}
	return (0);
}

static int	grab_forks(t_philo *p)
{
	int	right_fork;

	right_fork = p->num_philo + 1;
	if (p->num_philo == p->rules->num_philos - 1)
		right_fork = 0
	if (p->num_philo % 2 == 0)
	{
		pthread_mutex_lock(&(p->forks[p->num_philo]));
		printf("%lld %d has taken a fork\n", get_time_ms(), p->num_philo + 1);
		pthread_mutex_lock(&(p->forks[right_fork]));
		printf("%lld %d has taken a fork\n", get_time_ms(), p->num_philo + 1);
	}
	else
	{
		pthread_mutex_lock(&(p->forks[right_fork]));
		printf("%lld %d has taken a fork\n", get_time_ms(), p->num_philo + 1);
		pthread_mutex_lock(&(p->forks[p->num_philo]));
		printf("%lld %d has taken a fork\n", get_time_ms(), p->num_philo + 1);
	}
}

void	*start_routine(void *args)
{
	long long	time_to_die;
	t_philo		*philo;

	philo = (t_philo *)args;
	time_to_die = get_time_ms() + philo->rules->time_to_die;
	while (1)
	{
		if (check_for_death(philo, time_to_die))
			break;
	}
	return (NULL);
}