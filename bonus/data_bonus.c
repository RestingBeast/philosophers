/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.sg  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 16:44:09 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/07 16:44:10 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static void	init_data(t_data *data)
{
	data->rules = NULL;
	data->processes = NULL;
}

static int	check_argc(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!is_integer(argv[i]))
			return (0);
	}
	return (1);
}

/*
static pid_t	*create_processes()
{
}
*/

int	create_data(int argc, char **argv, t_data *data)
{
	if (!check_argc(argc, argv))
		return (fatal_error("Expected integers as arguements"));
	init_data(data);
	data->rules = create_rules(argc, argv);
	if (!data->rules)
		return (fatal_error("Malloc failed"));

	return (0);
}

void	clean_up(t_data *data)
{
	free(data->rules);
	free(data->processes);
}
