#include "philo.h"

void    *observer_routine(void *args)
{
    t_data  *data;
	int		done_threads;
	int		i;

    data = (t_data *) args;
    printf("Observer started!\n"); // To be deleted
    data->start_f = 1;
	while (1)
	{
		done_threads = 0;
		i = 0;
		while (i < data->rules->num_philos)
		{
			done_threads += data->philos[i]->done_f;
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