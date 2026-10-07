/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.sg  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 16:38:26 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/07 16:38:27 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;
	if (argc != 5 && argc != 6)
		return (fatal_error("Expected 4 or 5 arguements"));
	create_data(argc, argv, &data);
	clean_up(&data);
	return (0);
}
