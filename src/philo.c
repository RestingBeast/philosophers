/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 19:47:40 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/05/23 19:47:42 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static void	destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
}

static int	init_data(int argc, char **argv, t_data *data)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!is_integer(argv[i]))
			return (0);
	}
	data->num_philos = simple_atoi(argv[1]);
	data->time_to_die = simple_atoi(argv[2]);
	data->time_to_eat = simple_atoi(argv[3]);
	data->time_to_sleep = simple_atoi(argv[4]);
	if (argc == 6)
		data->meals_to_eat = simple_atoi(argv[5]);
	else
		data->meals_to_eat = 0;
	data->forks = init_forks(data->num_philos);
	if (!data->forks)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
//	int		i;
	t_data	data;

	if (argc != 5 && argc != 6)
		return (fatal_error("Expected 4 or 5 arguments"));
	if (init_data(argc, argv, &data) == 0)
		return (fatal_error("Expected integers as arguements"));
	destroy_forks(&data);
/*
	i = 0;
	while (i < num_thread)
	{
		if (pthread_create(&threads[i], NULL, do_nothing, NULL) != 0)
			return (1);
		pthread_mutex_init(mutexes[i], NULL);
		i++;
	}
	while (i-- > 0)
		pthread_join(threads[i], NULL);
*/
	return (0);
}
