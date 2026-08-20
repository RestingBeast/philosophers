/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 18:33:43 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/08/20 21:36:30 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*new_philo(t_data *data, int *start_f, int *death_f, int num)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->num_philo = num;
	philo->meals_left = data->rules->meals_to_eat;
	philo->rules = data->rules;
	philo->forks = data->forks;
	philo->start_f = start_f;
	philo->death_f = death_f;
	philo->done_f = 0;
	philo->death_timer = 0;
	philo->write_lock = &data->write_lock;
	philo->death_lock = &data->death_lock;
	philo->print_lock = &data->print_lock;
	philo->meal_lock = &data->meal_lock;
	return (philo);
}

t_philo	**create_philos(t_data *data, int *start_f, int *death_f)
{
	t_philo	**res;
	t_philo	*philo;
	int		i;

	res = malloc(data->rules->num_philos * sizeof(t_philo *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < data->rules->num_philos)
	{
		philo = new_philo(data, start_f, death_f, i);
		if (!philo)
		{
			while (i-- > 0)
				free(res[i]);
			return (free(res), NULL);
		}
		res[i++] = philo;
	}
	return (res);
}

static void	destroy_fork(int num_philos, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_destroy(&(forks[i]));
		i++;
	}
}

static void	free_philo(int num_philos, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		free(philos[i]);
		i++;
	}
}

void	clean_up(t_data *data)
{
	int	num_philo;

	num_philo = 0;
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->meal_lock);
	if (data->rules)
		num_philo = data->rules->num_philos;
	free(data->rules);
	destroy_fork(num_philo, data->forks);
	free(data->forks);
	free(data->threads);
	free_philo(num_philo, data->philos);
	free(data->philos);
}
