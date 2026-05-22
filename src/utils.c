# include "philo.h"

int    get_time_ms(void)
{
    struct timeval  time;

	gettimeofday(&time, NULL);
	return (time.tv_usec / 1000);
}