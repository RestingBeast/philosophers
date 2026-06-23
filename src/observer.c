#include "philo.h"

void    *observer_routine(void *args)
{
    t_data  *data;
	int		done_threads;
	int		i;

	data = (t_data *) args;
	printf("Observer started!\n"); // To be deleted
	pthread_mutex_lock(&data->write_lock);
	data->start_f = 1;
	pthread_mutex_unlock(&data->write_lock);
	while (1)
	{
		done_threads = 0;
		i = 0;
		while (i < data->rules->num_philos)
		{
			pthread_mutex_lock(&data->write_lock);
			done_threads += data->philos[i]->done_f;
			pthread_mutex_unlock(&data->write_lock);
			// death checking should be here!
			// if (data->philos[i]->done_f == 1)
			// {
			// 	i++;
			// 	continue ;
			// }
			i++;
		}
		if (done_threads == data->rules->num_philos)
			break;
		usleep(500000); // Change later
	}
	printf("Simulation finished!\n"); // To be deleted
    return (NULL);
}
