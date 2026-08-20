#include "philo.h"

static void	init_data(t_data *data)
{
	data->rules = NULL;
	data->forks = NULL;
	data->philos = NULL;
	data->threads = NULL;
	data->start_f = 0;
	data->death_f = 0;
	data->done_threads = 0;
}

static pthread_mutex_t	*create_forks(int num_philos)
{
	pthread_mutex_t	*res;
	int			i;

	res = malloc(num_philos * sizeof(pthread_mutex_t));
	if (!res)
		return (NULL);
	i = 0;
	while (i < num_philos)
	{
		if (pthread_mutex_init(&res[i], NULL) != 0)
			return (NULL);
		i++;
	}
	return (res);
}

static int	create_mutexes(t_data *data)
{
	if (pthread_mutex_init(&(data->write_lock), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(data->death_lock), NULL) != 0)
	{
		pthread_mutex_destroy(&data->write_lock);
		return (0);
	}
	if (pthread_mutex_init(&(data->print_lock), NULL) != 0)
	{
		pthread_mutex_destroy(&data->write_lock);
		pthread_mutex_destroy(&data->death_lock);
		return (0);
	}
	if (pthread_mutex_init(&(data->meal_lock), NULL) != 0)
	{
		pthread_mutex_destroy(&data->write_lock);
		pthread_mutex_destroy(&data->death_lock);
		pthread_mutex_destroy(&data->print_lock);
		return (0);
	}
	return (1);
}

int	create_data(int argc, char **argv, t_data *data)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!is_integer(argv[i]))
			return (fatal_error("Expected integers as arguements"));
	}
	init_data(data);
	if (!create_mutexes(data))
		return (fatal_error("Mutex Initialization Failed"));
	data->rules = create_rules(argc, argv);
	if (!data->rules)
		return (fatal_error("Malloc Failed"));
	if (data->rules->num_philos < 2)
		return (clean_up(data), fatal_error("Not enough fork!"));
	data->threads = malloc(data->rules->num_philos * sizeof(pthread_t));
	if (!data->threads)
		return (clean_up(data), fatal_error("Malloc Failed"));
	data->forks = create_forks(data->rules->num_philos);
	if (!data->forks)
		return (clean_up(data), fatal_error("Malloc Failed"));
	data->philos = create_philos(data, &(data->start_f), &(data->death_f));
	if (!data->philos)
		return (clean_up(data), fatal_error("Malloc Failed"));
	return (0);
}
