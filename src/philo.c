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
//	int		i;
	t_data	data;

	if (argc != 5 && argc != 6)
		return (fatal_error("Expected 4 or 5 arguments"));
	if (init_data(argc, argv, &data) != 0)
		return (EXIT_FAILURE);
	clean_up(&data);
	printf("Current time in ms: %ld\n", get_time_ms());
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
