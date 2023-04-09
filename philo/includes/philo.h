# ifndef PHILO_H
# define PHILO_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_philos
{
	int				philos_id;
	int				philos_len;
	int				num_of_eating;
	int				left_hand;
	int				right_hand;
	int				*forks;
	pthread_mutex_t	*mutex;
}	t_philos;
#endif