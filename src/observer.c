#include "philo.h"

static int	is_dead(t_philo *p)
{
	int	res;
	pthread_mutex_lock(p->meal_lock);
	if (get_time_ms() < p->last_meal + p->rules->time_to_die)
		res = 0;
	else
		res = 1;
	pthread_mutex_unlock(p->meal_lock);
	return (res);
}


void    *observer_routine(void *args)
{
	t_data	*data;
	int		done_threads;
	int		i;
	int		done;
	int		stop;

	stop = 0;
	data = (t_data *) args;
	toggle_flag(&data->write_lock, &data->start_f);
	usleep(10000);
	while (!stop)
	{
		done_threads = 0;
		i = 0;
		while (i < data->rules->num_philos)
		{
			done = get_flag(&data->write_lock, &data->philos[i]->done_f);
			done_threads += done;
			if (!done)
			{
				if (!get_flag(&data->death_lock, &data->death_f) && is_dead(data->philos[i]))
				{
					toggle_flag(&data->death_lock, &data->death_f);
					pthread_mutex_lock(&data->print_lock);
					printf("%lld %d died\n", get_time_ms(), i + 1);
					pthread_mutex_unlock(&data->print_lock);
					stop = 1;
				}
			}
			i++;
		}
		if (done_threads == data->rules->num_philos)
			break;
		usleep(10*1000); // Change later
	}
	return (NULL);
}
