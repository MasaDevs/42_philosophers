#include "../includes/philo.h"

t_philos    *make_philos(const t_info info, pthread_mutex_t *mutex, pthread_mutex_t *status)
{
	t_philos	*philos;
	int			i;

	i = 0;
	philos = malloc(sizeof(t_philos) * info.num_of_philos);
	if (!philos)
		return (NULL);
	while(i < info.num_of_philos)
	{
		philos[i].philos_id = i;
		philos[i].num_of_philos = info.num_of_philos;
		philos[i].time_to_eat = info.time_to_eat;
		philos[i].time_to_sleep = info.time_to_sleep;
		philos[i].status = status;
		philos[i].num_of_eat = info.num_of_eat;
		gettimeofday(&(philos[i].last_meal), NULL);
		philos[i].dead = 0;
		philos[i].right_hand = &(mutex[i]);
		philos[i].left_hand = &(mutex[(i + 1) % info.num_of_philos]);
		i++;
	}
	return (philos);
}

void	odd_philo_meal(t_philos *philo)
{
	int		i;

	i = 0;
	while(i < get_num_of_eat(philo) || get_num_of_eat(philo) < 0)
	{
		if (is_philo_dead(philo))
			return ;
		while (pthread_mutex_lock(philo->right_hand) != 0)
			;
		print_philos(philo, "has taken a fork");
		while(pthread_mutex_lock(philo->left_hand) != 0)
		{
			if (is_philo_dead(philo))
			{
				pthread_mutex_unlock(philo->right_hand);
				return ;
			}
		}
		print_philos(philo, "is eating");
		change_last_meal(philo);
		usleep(philo->time_to_eat * 1000);
		//change_last_meal(philo);
		pthread_mutex_unlock(philo->right_hand);
		pthread_mutex_unlock(philo->left_hand);
		print_philos(philo, "is sleeping");
		usleep(philo->time_to_sleep * 1000);
		print_philos(philo, "is thinking");
		if (0 < get_num_of_eat(philo))
			i++;
	}
	print_philos(philo, "died");
	set_philo_dead(philo);
}

void	even_philo_meal(t_philos *philo)
{
	int		i;

	i = 0;
	while(i < get_num_of_eat(philo) || get_num_of_eat(philo) < 0)
	{
		if (is_philo_dead(philo))
			return ;
		while (pthread_mutex_lock(philo->left_hand) != 0)
			;
		print_philos(philo, "has taken a fork");
		while(pthread_mutex_lock(philo->right_hand) != 0)
		{
			if (is_philo_dead(philo))
			{
				pthread_mutex_unlock(philo->left_hand);
				return ;
			}
		}
		print_philos(philo, "is eating");
		change_last_meal(philo);
		usleep(philo->time_to_eat * 1000);
		//change_last_meal(philo);
		pthread_mutex_unlock(philo->right_hand);
		pthread_mutex_unlock(philo->left_hand);
		print_philos(philo, "is sleeping");
		usleep(philo->time_to_sleep * 1000);
		print_philos(philo, "is thinking");
		if (0 < get_num_of_eat(philo))
			i++;
	}
	print_philos(philo, "died");
	set_philo_dead(philo);
}
