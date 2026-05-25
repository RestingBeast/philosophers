/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 20:00:58 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/05/23 20:00:59 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *routine)
{
	printf("Philosopher #%d is sleeping.", routine-> i))
	return (NULL);
}

void	init_routine(t_data *data, t_routine *routine, int i)
{
	data->fork1 = data->forks[i];
	if (i == data->num_philos - 1)
		data->fork2 = data->forks[0];
	else
		data->fork2 = data->forks[i + 1];
	data->time_to_eat = data->time_to_eat;
	data->time_to_think = data->time_to_think;
	data->time_to_sleep = data->time_to_sleep;
	data->meals_to_eat = data->meals_to_eat;
}
