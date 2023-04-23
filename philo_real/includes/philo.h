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
	int				num_of_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	struct timeval	last_meal;
	int				dead;
	pthread_mutex_t	status;
	pthread_mutex_t	*left_hand;
	pthread_mutex_t	*right_hand;
}	t_philos;

typedef struct s_info
{
	int	num_of_philos;
	int time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_eat;
}	t_info;
#endif
