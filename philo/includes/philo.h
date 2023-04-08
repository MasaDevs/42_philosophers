# ifndef PHILO_H
# define PHILO_H
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
typedef struct s_philos
{
	pthread_t	thread;
	int			fork;
	
}t_philos;
#endif