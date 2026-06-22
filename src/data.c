#include "philo.h"

static t_philo  **init_philos(t_data *data, volatile int *start_f, volatile int *death_f)
{
    t_philo **res;
    t_philo *philo;
    int     i;

    res = malloc(data->rules->num_philos * sizeof(t_philo *));
    if (!res)
        return (NULL);
    i = 0;
    while (i < data->rules->num_philos)
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
		philo->start_f = start_f;
		philo->death_f = death_f;
		philo->done_f = 0;
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

int	init_data(int argc, char **argv, t_data *data)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!is_integer(argv[i]))
			return (fatal_error("Expected integers as arguements"));
	}
	data->start_f = 0;
	data->death_f = 0;
	data->rules = init_rules(argc, argv);
	if (!data->rules)
		return (fatal_error("Malloc Failed"));
	data->threads = malloc(data->rules->num_philos * sizeof(pthread_t));
	if (!data->threads)
		return (free(data->rules), fatal_error("Malloc Failed"));
	data->forks = init_forks(data->rules->num_philos);
	if (!data->forks)
		return (free(data->rules), free(data->threads),
			fatal_error("Malloc Failed"));
	data->philos = init_philos(data, &(data->start_f), &(data->death_f));
	if (!data->philos)
		return (free(data->rules), free(data->forks),
			free(data->threads), fatal_error("Malloc Failed"));
	return (0);
}

void	clean_up(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		free(data->philos[i]);
		i++;
	}
	free(data->forks);
	free(data->rules);
	free(data->threads);
	free(data->philos);
}
