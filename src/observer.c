#include "philo.h"

void    *observer_routine(void *args)
{
    t_data  *data;

    data = (t_data *) args;
    printf("Observer started!\n");
    data->start_f = 1;
    return (NULL);
}