#include "../includes/philo.h"

int	is_philo_dead(t_philos *philo)
{
	int flag;

	flag = 0;
	if (philo->dead)
		flag = 1;
	return (flag);
}

int get_num_of_eat(t_philos *philo)
{
	int num_of_eat;

	num_of_eat = philo->num_of_eat;
	return (num_of_eat);
}

void	set_philo_dead(t_philos *philo)
{
	while(pthread_mutex_lock((philo->status)) != 0)
		;
	philo->dead = 1;
	pthread_mutex_unlock((philo->status));
}

void change_last_meal(t_philos *philo)
{
	while (pthread_mutex_lock((philo->status)) != 0)
		;
	gettimeofday(&(philo->last_meal), NULL);
	pthread_mutex_unlock((philo->status));
}

void	print_philos(t_philos *philo, char *str)
{
	struct timeval	tp;

	while (pthread_mutex_lock((philo->status)) != 0)
		;
	if(philo->dead)
	{
		pthread_mutex_unlock((philo->status));
		return ;
	}
	gettimeofday(&tp, NULL);
	printf("%ld %d %s\n", tp.tv_sec * 1000 + tp.tv_usec / 1000, philo->philos_id + 1, str);
	pthread_mutex_unlock((philo->status));
}
