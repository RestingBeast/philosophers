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

t_routine	*init_routine(int argc, char **argv)
{
	t_routine	*routine;

	routine = malloc(sizeof(t_routine));
	if (!routine)
		return (NULL);
	routine->time_to_die = simple_atoi(argv[2]);
	routine->time_to_eat = simple_atoi(argv[3]);
	routine->time_to_sleep = simple_atoi(argv[4]);	
	if (argc == 6)
		routine->meals_to_eat = simple_atoi(argv[5]);
	else
		routine->meals_to_eat = 0;
	return (routine);
}
