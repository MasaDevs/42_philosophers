#include "../includes/philo.h"
void	odd_philo_meal(t_philos *philo);
void	even_philo_meal(t_philos *philo);
int	time_to_meal(t_philos *philo);

void	*calc(void *philos);
void	print_philos(t_philos *philo, char *str);
int	monitor(t_philos *philo);

#define num_of_philos 5
#define time_to_die 1000
#define time_to_eat 100
#define time_to_sleep 100
#define number_of_times_each_philosopher_must_eat 2

int	main(void)
{
	pthread_t		thread[num_of_philos + 1];
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
		philos[i].dead = 0;
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
		if(monitor(philos))
			break;

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
		if (philo->dead)
			return ;
		while (pthread_mutex_lock(philo->right_hand) != 0)
			;
		print_philos(philo, "has taken fork");
		while(pthread_mutex_lock(philo->left_hand) != 0)
			;
		print_philos(philo, "eating");
		usleep(time_to_eat);
		pthread_mutex_unlock(philo->right_hand);
		pthread_mutex_unlock(philo->left_hand);
		print_philos(philo, "is sleeping");
		usleep(time_to_sleep);
		print_philos(philo, "is thinking");
		i++;
	}
	print_philos(philo, "is dead");
	philo->dead = 1;
}

void	even_philo_meal(t_philos *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->num_of_eating)
	{
		if (philo->dead)
			return ;
		while (pthread_mutex_lock(philo->left_hand) != 0)
			;
		print_philos(philo, "has taken fork");
		while(pthread_mutex_lock(philo->right_hand) != 0)
			;
		print_philos(philo, "is eating");
		usleep(time_to_eat);
		pthread_mutex_unlock(philo->right_hand);
		pthread_mutex_unlock(philo->left_hand);
		print_philos(philo, "is sleeping");
		usleep(time_to_sleep);
		print_philos(philo, "is thinking");
		i++;
	}
	print_philos(philo, "is dead");
	philo->dead = 1;
}

int	monitor(t_philos *philo)
{
	int				len;
	int				i;
	int				flag;
	struct timeval	tp;

	i = 0;
	flag = 1;
	gettimeofday(&tp, NULL);
	while(i < num_of_philos)
	{
		while(pthread_mutex_lock(philo[i].right_hand) != 0)
			;
		while(pthread_mutex_lock(philo[i].left_hand) != 0)
			;
		if (!(philo[i].dead))
			flag = 0;
		if(tp.tv_usec - (philo[i].tp).tv_usec > time_to_die && !(philo[i].dead))
		{
			print_philos(&(philo[i]), "is dead");
			philo[i].dead = 1;
		}
		pthread_mutex_unlock(philo[i].left_hand);
		pthread_mutex_unlock(philo[i].right_hand);
		i++;
	}
	if (flag)
		return (1);
	return (0);
}

void	print_philos(t_philos *philo, char *str)
{
	struct timeval	tp;

	if(philo->dead)
		return ;
	gettimeofday(&tp, NULL);
	printf("%d %d %s\n", tp.tv_usec, philo->philos_id, str);
	if(!strcmp(str, "is eating"))
		memcpy(&(philo->tp), &tp, sizeof(tp));
}