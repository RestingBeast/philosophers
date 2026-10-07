/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.sg  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 16:16:42 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/07 16:16:44 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>

typedef struct s_rules	t_rules;
typedef struct s_data	t_data;

struct s_rules
{
	int			num_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meals_to_eat;
	long long	strat_time;
};

struct s_data
{
	t_rules	*rules;
	pid_t	*processes;
};

// data.c
int	create_data(int argc, char **argv, t_data *data);
void	clean_up(t_data *data);

// rules.c
t_rules		*create_rules(int argc, char **argv);

// utils.c
long long	get_time_ms(void);
int			is_integer(char *str);
int			simple_atoi(char *str);
int			fatal_error(char *msg);

#endif
