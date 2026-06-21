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

int	main(int argc, char **argv)
{
	int		i;
	t_data	data;

	if (argc != 5 && argc != 6)
		return (fatal_error("Expected 4 or 5 arguments"));
	if (init_data(argc, argv, &data) != 0)
		return (EXIT_FAILURE);
	i = 0;
	while (i < data.rules->num_philos)
	{
		if (pthread_create(&(data.threads[i]), NULL, philo_routine,
			(void *) data.philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&(data.observer), NULL, observer_routine, (void *) &data) != 0)
		return (1);
	pthread_join(data.observer, NULL);
	while (i-- > 0)
		pthread_join(data.threads[i], NULL);
	clean_up(&data);
	return (0);
}
