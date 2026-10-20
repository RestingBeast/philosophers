#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	precise_sleep(int time_ms, t_philo *p)
{
	long long	wait_time;

	wait_time = get_time_ms() + time_ms;
	while (get_time_ms() < wait_time)
	{
		if (p && get_flag(p->death_lock, p->death_f))
			break ;
		usleep(500);
	}
}
