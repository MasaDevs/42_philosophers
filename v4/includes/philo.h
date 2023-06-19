#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philos
{
	int				philos_id;
	int				num_of_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	bool			finished;
	struct timeval	last_meal;
	bool			*someone_dead;
	pthread_mutex_t	status;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*left_hand;
	pthread_mutex_t	*right_hand;
}					t_philos;

typedef struct s_info
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	bool			*someone_dead;
}					t_info;

//info.c
int					set_info(t_info *info, int argc, char *argv[]);
pthread_mutex_t		*make_mutex(const t_info info);
pthread_t			*make_thread(t_info info, t_philos *philos);
void				*alloc(void *philos);

//philos.c
t_philos			*make_philos(const t_info info, pthread_mutex_t *mutex, pthread_mutex_t *dead);
void				even_philo_meal(t_philos *philo);
void				odd_philo_meal(t_philos *philo);

//operation
bool				is_philo_dead(t_philos philo);
int					get_num_of_eat(t_philos philo);
void				set_philo_dead(t_philos philo);
void				change_last_meal(t_philos *philo);
void				print_philos(t_philos philo, char *str);
void				set_finished(t_philos *philo);

#endif
