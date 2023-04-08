# ifndef PHILO_H
# define PHILO_H
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_philos
{
	int				*forks;
	int				philos_id;
	int				philos_len;
	pthread_mutex_t	mutex;
}	t_philos;
#endif