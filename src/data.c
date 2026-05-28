#include "philo.h"

static t_philo  **init_philosophers(t_data *data, int *flag)
{
    t_philo **res;
    t_philo *philo;
    int     i;

    res = malloc(data->num_philos * sizeof(t_philo *));
    if (!res)
        return (NULL);
    i = 0;
    while (i < data->num_philos)
    {
        philo = malloc(sizeof(t_philo));
        if (!philo)
        {
            while (i-- > 0)
                free(res[i]);
            return (free(res), NULL);
        }
        philo->num_philo = i;
        philo->rules = data->rules;
        philo->forks = data->forks;
	philo->someone_died = flag;
        res[i++] = philo;
    }
    return (res);
}

static pthread_mutex_t	*init_forks(int num_philos)
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

int	init_data(int argc, char **argv, t_data *data, int *flag)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!is_integer(argv[i]))
			return (fatal_error("Expected integers as arguements"));
	}
	data->num_philos = simple_atoi(argv[1]);
	data->rules = init_rules(argc, argv);
	if (!data->rules)
		return (fatal_error("Malloc Failed"));
	data->threads = malloc(data->num_philos * sizeof(pthread_t));
	if (!data->threads)
		return (free(data->rules), fatal_error("Malloc Failed"));
	data->forks = init_forks(data->num_philos);
	if (!data->forks)
		return (free(data->rules), free(data->threads),
			fatal_error("Malloc Failed"));
	data->philosophers = init_philosophers(data, flag);
	if (!data->philosophers)
		return (free(data->rules), free(data->forks),
			free(data->threads), fatal_error("Malloc Failed"));
	return (0);
}

void	clean_up(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		free(data->philosophers[i]);
		i++;
	}
	free(data->forks);
	free(data->rules);
	free(data->threads);
	free(data->philosophers);
}
