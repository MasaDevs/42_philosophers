#include "../includes/philo.h"

int	set_info(t_info *info, int argc, char *argv[]);
pthread_mutex_t	*make_mutex(const t_info info);
t_philos *make_philos(const t_info info, pthread_mutex_t *mutex);
pthread_t	*make_thread(t_info info, t_philos *philos);
void	destructor(const t_info info, pthread_t *thread, t_philos *philos, pthread_mutex_t *mutex);
void	*alloc(void *philos);

int	main(int argc, char *argv[])
{
	t_info			info;
	t_philos		*philos;
	pthread_mutex_t	*mutex;
	pthread_t		*thread;

	if(argc < 5 || 6 < argc)
		return (0);
	set_info(&info, argc, argv);
	mutex = make_mutex(info);
	philos = make_philos(info, mutex);
	thread = make_thread(info, philos);
	destructor(info, thread, philos, mutex);
	free(thread);
	free(philos);
	free(mutex);
	
}

//const might be better choice.
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

t_philos *make_philos(const t_info info, pthread_mutex_t *mutex)
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
		philos[i].num_of_eat = info.num_of_eat;
		gettimeofday(&(philos[i].last_meal), NULL);
		philos[i].dead = 0;
		pthread_mutex_init(&(philos[i].status), NULL);
		philos[i].right_hand = &(mutex[i]);
		philos[i].left_hand = &(mutex[(i + 1) % info.num_of_philos]);
		i++;
	}
	return (philos);
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

void	odd_philo_meal(t_philos *philo)
{
	int		i;

	while(i < philo->num_of_eat)
	{
		if (is_philo_dead(philo))
			return ;
		while (pthread_mutex_lock(philo->right_hand) != 0)
			;
		print_philos(philo, "has taken a fork");
		while(pthread_mutex_lock(philo->left_hand) != 0)
			;
		change_last_meal(philo);
		print_philos(philo, "is eating");
		usleep(philo->time_to_eat * 1000);
		change_last_meal(philo);
		pthread_mutex_unlock(philo->right_hand);
		pthread_mutex_unlock(philo->left_hand);
		print_philos(philo, "is sleeping");
		usleep(philo->time_to_sleep * 1000);
		print_philos(philo, "is thinking");
		if (0 < philo->num_of_eat)
			i++;
	}
	print_philos(philo, "died");
	philo->dead = 1;
}

int	is_philo_dead(t_philos *philo)
{
	int flag;

	flag = 0;
	while (pthread_mutex_lock(&(philo->status)) != 0)
		;
	if (philo->dead)
		flag = 1;
	pthread_mutex_unlock(&(philo->status));
	return (flag);
}

void change_last_meal(t_philos *philo)
{
	while (pthread_mutex_lock(&(philo->status)) != 0)
		;
	gettimeofday(&(philo->last_meal), NULL);
	pthread_mutex_unlock(&(philo->status));
}

void	destructor(const t_info info, pthread_t *thread, t_philos *philos, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	while (i < info.num_of_philos)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	i = 0;
	while (i < info.num_of_philos)
	{
		pthread_mutex_destroy(&(mutex[i]));
		pthread_mutex_destroy(&(philos[i].status));
		i++;
	}
}
//malloc
//mutex
//thread
//philos