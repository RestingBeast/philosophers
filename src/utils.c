# include "philo.h"

int	get_time_ms(void)
{
    struct timeval  time;

	gettimeofday(&time, NULL);
	return (time.tv_usec / 1000);
}

int	validate_input(char *str)
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

