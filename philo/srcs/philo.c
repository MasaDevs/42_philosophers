#include "../includes/philo.h"
void	odd_philo_meal(t_philos *philo);
void	even_philo_meal(t_philos *philo);
int	time_to_meal(t_philos *philo);

void	*calc(void *philos);

#define num_of_philos 5
#define time_to_die 1000
#define time_to_eat 100
#define time_to_sleep 100
#define number_of_times_each_philosopher_must_eat 2

int	main(void)
{
	pthread_t		thread[num_of_philos];
	t_philos		philos[num_of_philos];
	pthread_mutex_t	mutex[num_of_philos];
	int				i;

	//init mutex
	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_init(&(mutex[i]), NULL);
		i++;
	}

	//init philos
	i = 0;
	while (i < num_of_philos)
	{
		philos[i].philos_id = i;
		philos[i].philos_len = num_of_philos;
		philos[i].num_of_eating = number_of_times_each_philosopher_must_eat;
		philos[i].right_hand = &(mutex[i]);
		philos[i].left_hand = &(mutex[(i + 1) % num_of_philos]);
		i++;
	}

	//init thread
	i = 0;
	while (i < num_of_philos)
	{
		pthread_create(&thread[i], NULL, calc, (void *)&philos[i]);
		i++;
	}
	while (1)
		;
	//dest mutex
	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_destroy(&(mutex[i]));
		i++;
	}
	return (0);
}

void	*calc(void *philos)
{
	t_philos	*philo;

	philo = (t_philos *)philos;
	if (philo->philos_id % 2)
		odd_philo_meal(philo);
	else
		even_philo_meal(philo);
	return (NULL);
}

void	odd_philo_meal(t_philos *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->num_of_eating)
	{
		while (pthread_mutex_lock(philo->right_hand) != 0)
			;
		printf("philo %d thinking\n", philo->philos_id);
		while(pthread_mutex_lock(philo->left_hand) != 0)
			;
		printf("philo %d eating\n", philo->philos_id);
		usleep(time_to_eat);
		pthread_mutex_unlock(philo->right_hand);
		pthread_mutex_unlock(philo->left_hand);
		printf("philo %d sleeping\n", philo->philos_id);
		usleep(time_to_sleep);
		i++;
	}
}

void	even_philo_meal(t_philos *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->num_of_eating)
	{
		while (pthread_mutex_lock(philo->left_hand) != 0)
			;
		printf("philo %d thinking\n", philo->philos_id);
		while(pthread_mutex_lock(philo->right_hand) != 0)
			;
		printf("philo %d eating\n", philo->philos_id);
		usleep(time_to_eat);
		pthread_mutex_unlock(philo->right_hand);
		pthread_mutex_unlock(philo->left_hand);
		printf("philo %d sleeping\n", philo->philos_id);
		usleep(time_to_sleep);
		i++;
	}
}
