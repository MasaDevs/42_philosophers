# ifndef PHILO_H
# define PHILO_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <pthread.h>

typedef struct s_philos
{
	int				philos_id;
	int				philos_len;
	int				num_of_eating;
	struct timeval	tp;
	int				dead;
	pthread_mutex_t	status;
	pthread_mutex_t	*left_hand;
	pthread_mutex_t	*right_hand;
}	t_philos;
#endif
