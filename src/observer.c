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

static	void	report_death(t_philo *p)
{
	long long	timestamp;

	pthread_mutex_lock(p->print_lock);
	pthread_mutex_lock(p->death_lock);
	*(p->death_f) = 1;
	timestamp = get_time_ms() - p->rules->start_time;
	printf("%lld %d died\n", timestamp, p->num_philo + 1);
	pthread_mutex_unlock(p->death_lock);
	pthread_mutex_unlock(p->print_lock);
}

static void	check_philosophers(t_philo **p, int num_philos, t_observer *obs)
{
	int	i;
	int	done;

	i = -1;
	obs->done_threads = 0;
	while (++i < num_philos)
	{
		done = get_flag(p[i]->write_lock, &p[i]->done_f);
		obs->done_threads += done;
		if (done)
			continue ;
		if (get_time_ms() >= get_death_timer(p[i]->meal_lock,
				&p[i]->death_timer))
		{
			report_death(p[i]);
			obs->stop = 1;
			return ;
		}
	}
}

static void	set_philos_death_timer(int num_philos, t_philo **p)
{
	int	i;

	i = -1;
	while (++i < num_philos)
		p[i]->death_timer = p[i]->rules->start_time + p[i]->rules->time_to_die;
}

void	*observer_routine(void *args)
{
	t_data		*data;
	t_observer	obs;

	data = (t_data *) args;
	init_observer(&obs);
	pthread_mutex_lock(&data->write_lock);
	data->rules->start_time = get_time_ms() + 10;
	set_philos_death_timer(data->rules->num_philos, data->philos);
	data->start_f = 1;
	pthread_mutex_unlock(&data->write_lock);
	while (!obs.stop)
	{
		check_philosophers(data->philos, data->rules->num_philos, &obs);
		if (obs.done_threads == data->rules->num_philos)
			break ;
		precise_sleep(1, NULL);
	}
	return (NULL);
}
