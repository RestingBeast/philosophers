/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 17:38:52 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/08/12 17:38:53 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_observer(t_observer *obs)
{
	obs->stop = 0;
	obs->done_threads = 0;
}

static long long	get_death_timer(pthread_mutex_t *lock, long long *time)
{
	long long	res;

	pthread_mutex_lock(lock);
	res = *time;
	pthread_mutex_unlock(lock);
	return (res);
}

static	void	report_death(t_philo *p)
{
	pthread_mutex_lock(p->death_lock);
	pthread_mutex_lock(p->print_lock);
	*(p->death_f) = 1;
	printf("%lld %d died\n", get_time_ms(), p->num_philo + 1);
	pthread_mutex_unlock(p->print_lock);
	pthread_mutex_unlock(p->death_lock);
}

static void	check_philosophers(t_philo **p, int num_philos, t_observer *obs)
{
	int	i;
	int	done;

	i = -1;
	obs->done_threads = 0;
	while (++i < num_philos)
	{
		if (get_death_timer(p[i]->meal_lock, &p[i]->death_timer) == 0)
			continue ;
		done = get_flag(p[i]->write_lock, &p[i]->done_f);
		obs->done_threads += done;
		if (done)
			continue ;
		if (get_time_ms() >= get_death_timer(p[i]->meal_lock, &p[i]->death_timer))
		{
			report_death(p[i]);
			obs->stop = 1;
			return ;
		}
	}
}

void	*observer_routine(void *args)
{
	t_data		*data;
	t_observer	obs;

	data = (t_data *) args;
	init_observer(&obs);
	toggle_flag(&data->write_lock, &data->start_f);
	while (!obs.stop)
	{
		check_philosophers(data->philos, data->rules->num_philos, &obs);
		if (obs.done_threads == data->rules->num_philos)
			break ;
		usleep(10 * 1000);
	}
	return (NULL);
}
