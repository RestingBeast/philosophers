#include "philo.h"

static void	check_philosophers(t_philo **p, int num_philos, t_observer *obs)
{
	int	i;
	int	done;

	i = -1;
	while (++i < num_philos)
	{
		if (p[i]->last_meal = 0)
			break ;
		done = get_flag(p[i]->write_lock, p[i]->done_f);
		obs->done_threads += done;
		if (done)
			continue ;
	}
}

void	*observer_routine(void *args)
{
	t_data		*data;
	t_observer	obs;

	data = (t_data *) args;
	init_observer(&obs);
	toggle_flag(&data->write_lock, &data->start_f);
	while (!obs->stop)
	{
		// call check_philosophers
		if (obs->done_threads == data->rules->num_philos)
			break;
		usleep(10 * 1000);
	}
	return (NULL);
}
