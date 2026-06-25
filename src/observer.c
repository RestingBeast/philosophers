#include "philo.h"

void    *observer_routine(void *args)
{
    t_data  *data;
	int		done_threads;
	int		i;
	int		done;
	int		stop;

	stop = 0;
    data = (t_data *) args;
    printf("Observer started!\n"); // To be deleted
	toggle_flag(&data->write_lock, &data->start_f);
	while (!stop)
	{
		usleep(500 * 1000);
		done_threads = 0;
		i = 0;
		while (i < data->rules->num_philos)
		{
			done = get_flag(&data->write_lock, &data->philos[i]->done_f);
			done_threads += done;
			if (!done)
			{
				if (i == 2)
				{
					toggle_flag(&data->death_lock, &data->death_f);
					printf("%lld %d died\n", get_time_ms(), i + 1);
					stop = 1;
				}
			}
			i++;
		}
		if (done_threads == data->rules->num_philos)
			break;
		usleep(500000); // Change later
	}
	printf("Simulation finished!\n"); // To be deleted
    return (NULL);
}
