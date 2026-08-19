/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 21:07:27 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/06/27 21:07:28 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	toggle_flag(pthread_mutex_t *lock, int *flag)
{
	pthread_mutex_lock(lock);
	*flag = !(*flag);
	pthread_mutex_unlock(lock);
}

int	get_flag(pthread_mutex_t *lock, int *flag)
{
	int	res;

	pthread_mutex_lock(lock);
	res = *flag;
	pthread_mutex_unlock(lock);
	return (res);
}

void	print_status(t_philo *p, const char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(p->print_lock);
	if (get_flag(p->death_lock, p->death_f) == 0)
	{
		timestamp = get_time_ms() - p->rules->start_time;
		printf("%lld %d %s\n", timestamp, p->num_philo + 1, msg);
	}
	pthread_mutex_unlock(p->print_lock);
}

void	update_death_timer(t_philo *p)
{
	pthread_mutex_lock(p->meal_lock);
	p->death_timer = get_time_ms() + p->rules->time_to_die;
	pthread_mutex_unlock(p->meal_lock);
}
