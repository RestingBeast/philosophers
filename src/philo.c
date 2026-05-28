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

void	*do_nothing(void *args)
{
	printf("%d\n", ((t_philo *) args)->num_philo);
	return (NULL);
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	data;

	if (argc != 5 && argc != 6)
		return (fatal_error("Expected 4 or 5 arguments"));
	if (init_data(argc, argv, &data) != 0)
		return (EXIT_FAILURE);
	i = 0;
	while (i < data.num_philos)
	{
		if (pthread_create(&(data.threads[i]), NULL, do_nothing,
			(void *) data.philosophers[i]) != 0)
			return (1);
		i++;
	}
	while (i-- > 0)
		pthread_join(data.threads[i], NULL);
	clean_up(&data);
	return (0);
}
