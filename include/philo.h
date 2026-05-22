#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data   t_data;
struct s_data
{
    int num_philos;
    int num_forks;
    int time_to_eat;
    int time_to_think;
    int time_to_sleep;
    int meals_per_philosopher;
}

int    get_time_ms(void);
#endif