#include "../includes/philo.h"
void	odd_philo_meal(t_philos *philo);
void	even_philo_meal(t_philos *philo);
int	time_to_meal(t_philos *philo);

void	*calc(void *philos);

#define num_of_philos 5
#define time_to_die 100
#define time_to_eat 100
#define time_to_sleep 100
#define number_of_times_each_philosopher_must_eat 2

int	main(void)
{
	pthread_t		thread[num_of_philos];
	t_philos		philos[num_of_philos];
	pthread_mutex_t	mutex;
	int				i;

	int fork[num_of_philos] = {1, 1, 1, 1, 1};
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < num_of_philos)
	{
		philos[i].forks = fork;
		philos[i].philos_id = i;
		philos[i].philos_len = num_of_philos;
		philos[i].mutex = &mutex;
		philos[i].num_of_eating = number_of_times_each_philosopher_must_eat;
		i++;
	}
	i = 0;
	while (i < num_of_philos)
	{
		pthread_create(&thread[i], NULL, calc, (void *)&philos[i]);
		i++;
	}
	while (1)
		;
	pthread_mutex_destroy(&mutex);
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
			while (!(philo->forks[philo->philos_id - 1]) && !philo->right_hand)
				;
			pthread_mutex_lock(philo->mutex);
			if (philo->forks[philo->philos_id - 1])
			{
				philo->forks[philo->philos_id - 1] = 0;
				philo->right_hand = 1;
			}
			pthread_mutex_unlock(philo->mutex);
			if (!philo->right_hand)
				continue;
			printf("philo %d thinking\n", philo->philos_id);
			while(!(philo->forks[philo->philos_id]) && !philo->left_hand)
				;
			pthread_mutex_lock(philo->mutex);
			if ((philo->forks[philo->philos_id]))
			{
				philo->forks[philo->philos_id] = 0;
				philo->left_hand = 1;
			}
			pthread_mutex_unlock(philo->mutex);
			if (!philo->left_hand)
				continue;
			if (time_to_meal(philo))
				i++;
		}
}

void	even_philo_meal(t_philos *philo)
{
	size_t	i;
	int		right_hand;

	i = 0;
	while (i < philo->num_of_eating)
	{
		while(!(philo->forks[philo->philos_id]) && !philo->left_hand)
			;
		pthread_mutex_lock(philo->mutex);
		if ((philo->forks[philo->philos_id]))
		{
			philo->forks[philo->philos_id] = 0;
			philo->left_hand = 1;
		}
		pthread_mutex_unlock(philo->mutex);
		if (!philo->left_hand)
			continue;
		printf("philo %d thinking\n", philo->philos_id);
		right_hand = philo->philos_id - 1;
		if (right_hand < 0)
			right_hand = philo->philos_len - 1;
		while (!(philo->forks[right_hand]) && !philo->right_hand)
			;
		pthread_mutex_lock(philo->mutex);
		if (philo->forks[right_hand])
		{
			philo->forks[right_hand] = 0;
			philo->right_hand = 1;
		}
		pthread_mutex_unlock(philo->mutex);
		if (!philo->right_hand)
			continue;
		if (time_to_meal(philo))
			i++;
	}
}

int	time_to_meal(t_philos *philo)
{
	if (philo->left_hand != 1 || philo->left_hand != 1)
		return 0;
	printf("philo %d eating\n", philo->philos_id);
	usleep(time_to_eat);
	pthread_mutex_lock(philo->mutex);
	philo->left_hand = 0;
	philo->right_hand = 0;
	philo->forks[philo->philos_id] = 1;
	if (0 < philo->philos_id)
		philo->forks[philo->philos_id - 1] = 1;
	else
		philo->forks[philo->philos_len - 1] = 1;
	printf("philo %d sleeping\n", philo->philos_id);
	pthread_mutex_unlock(philo->mutex);
	usleep(time_to_sleep);
	return (1);
}