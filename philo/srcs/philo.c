#include "../includes/philo.h"

void	*calc(void	*philos);

#define num_of_philos 10

int main(void)
{
	pthread_t	thread[num_of_philos];
	int			fork[num_of_philos] = {1, 1, 1, 1 ,1, 1, 1, 1, 1, 1};
	t_philos	philos[num_of_philos];
	int			i;

	
	i = 0;
	while (i < num_of_philos)
	{
		philos[i].forks = fork;
		philos[i].philos_id = i;
		philos[i].philos_len = num_of_philos;
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
	
	return 0;
}

void	*calc(void	*philos)
{
	t_philos	*philo;

	philo = (t_philos *)philos;
	printf("%d\n", philo->philos_id);
	return (NULL);
}