/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 03:59:10 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/21 03:59:10 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	precise_sleep(int time_ms, t_philo *p)
{
	long long	wait_time;

	wait_time = get_time_ms() + time_ms;
	while (get_time_ms() < wait_time)
	{
		if (p && get_flag(p->death_lock, p->death_f))
			break ;
		usleep(500);
	}
}

void	stagger_philos(t_philo *p)
{
	int	stagger;
	int	eat;
	int	sleep;

	eat = p->rules->time_to_eat;
	sleep = p->rules->time_to_sleep;
	stagger = (2 * eat) - sleep;
	if (stagger > 0)
		precise_sleep(stagger, p);
}

long long	get_death_timer(pthread_mutex_t *lock, long long *time)
{
	long long	res;

	pthread_mutex_lock(lock);
	res = *time;
	pthread_mutex_unlock(lock);
	return (res);
}
