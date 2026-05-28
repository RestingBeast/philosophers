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

void	*start_routine(void *args)
{
	long long	time_to_die;
	t_philo		*philo;

	philo = (t_philo *)args;
	if (philo->num_philo != 2)
	{
		while (1)
		{
			usleep(10);
			if (*(philo->someone_died))
				break;
		}
	}
	else
	{
		time_to_die = get_time_ms() + philo->rules->time_to_die;
		while (1)
		{
			usleep(10);
			if (get_time_ms() > time_to_die)
			{
				*(philo->someone_died) = 1;
				break;
			}
		}
	}
	return (NULL);
}
