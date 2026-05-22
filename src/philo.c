# include "philo.h"

void	*do_nothing(void* arg)
{
	sleep(5);
	printf("Sleep completed\n");
	return (NULL);
}

int	main(int argc, char **argv)
{
	int num_thread = 5;
	pthread_t threads[num_thread];
	pthread_mutex_t	mutexes[num_thread]
	int	i = 0;
    // if (argc != 5 && argc != 6)
	// {
    //     printf("Usage Error: Need 4 arguements\n");
    //     return (1);
	// }

	while (i < num_thread)
	{
		if (pthread_create(&threads[i], NULL, do_nothing, NULL) != 0)
			return (1);
		pthread_mutex_init(mutexes[i], NULL);
		i++;
	}
	while (i-- > 0)
		pthread_join(threads[i], NULL);
	printf("%d\n", get_time_ms());
    return (0);
}