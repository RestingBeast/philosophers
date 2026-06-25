#include "philo.h"

t_rules	*init_rules(int argc, char **argv)
{
	t_rules	*rules;

	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (NULL);
	rules->num_philos = simple_atoi(argv[1]);
	rules->time_to_die = simple_atoi(argv[2]);
	rules->time_to_eat = simple_atoi(argv[3]);
	rules->time_to_sleep = simple_atoi(argv[4]);	
	if (argc == 6)
		rules->meals_to_eat = simple_atoi(argv[5]);
	else
		rules->meals_to_eat = -1;
	return (rules);
}