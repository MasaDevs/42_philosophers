#include "../includes/philo.h"


int	set_info(t_info *info, int argc, char *argv[])
{
	info->num_of_philos = atoi(argv[1]);
	info->time_to_die = atoi(argv[2]);
	info->time_to_eat = atoi(argv[3]);
	info->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		info->num_of_eat = atoi(argv[5]);
	else
		info->num_of_eat = -1;
	return (1);
}

pthread_mutex_t	*make_mutex(const t_info info)
{
	pthread_mutex_t	*mutex;
	int				i;
	mutex = malloc(sizeof(pthread_mutex_t) * info.num_of_philos);
	if (!mutex)
		return (NULL);
	i = 0;
	while(i < info.num_of_philos)
	{
		pthread_mutex_init(&(mutex[i]), NULL);
		i++;
	}
	return (mutex);
}

pthread_t	*make_thread(t_info info, t_philos *philos)
{
	pthread_t	*thread;
	int			i;

	thread = malloc(sizeof(pthread_t) * info.num_of_philos);
	if (!thread)
		return (NULL);
	i = 0;
	while (i < info.num_of_philos)
	{
		pthread_create(&(thread[i]), NULL, alloc, (void *)&(philos[i]));
		i++;
	}
	return (thread);
	
}

void	*alloc(void *philos)
{
	t_philos	*philo;

	philo = (t_philos *)philos;
	if (philo->philos_id % 2)
		odd_philo_meal(philo);
	else
		even_philo_meal(philo);
	return (NULL);
}
