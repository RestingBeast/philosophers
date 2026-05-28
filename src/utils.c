/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 19:47:46 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/05/23 19:47:47 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	is_integer(char *str)
{
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	simple_atoi(char *str)
{
	int	res;

	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (res);
}

int	fatal_error(char *msg)
{
	printf("%s\n", msg);
	return (EXIT_FAILURE);
}

t_rules	*init_rules(int argc, char **argv)
{
	t_rules	*rules;

	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (NULL);
	rules->time_to_die = simple_atoi(argv[2]);
	rules->time_to_eat = simple_atoi(argv[3]);
	rules->time_to_sleep = simple_atoi(argv[4]);	
	if (argc == 6)
		rules->meals_to_eat = simple_atoi(argv[5]);
	else
		rules->meals_to_eat = 0;
	return (rules);
}
