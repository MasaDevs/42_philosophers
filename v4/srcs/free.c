#include "../includes/philo.h"

void	all_free(t_info *info, pthread_mutex_t *mutex, t_philos *philos,
		pthread_t *thread)
{
	if (info)
		free(info->someone_dead);
	if (mutex)
		free(mutex);
	if (thread)
		free(thread);
	if (philos)
		free(philos);
}
