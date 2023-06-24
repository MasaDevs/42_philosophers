/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:15:36 by marai             #+#    #+#             */
/*   Updated: 2023/06/25 03:16:53 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			monitor(t_info info, t_philos *philos);
void		destruct(t_info *info, pthread_t *thread, t_philos *philos,
				pthread_mutex_t *mutex);

int	main(int argc, char *argv[])
{
	t_info			info;
	t_philos		*philos;
	pthread_mutex_t	dead;
	pthread_mutex_t	*mutex;
	pthread_t		*thread;

	if (!is_arg_correct(argc, argv) || !set_info(&info, argc, argv))
		return (1);
	mutex = make_mutex(info);
	if (!mutex)
		return (1);
	pthread_mutex_init(&dead, NULL);
	philos = make_philos(info, mutex, &dead);
	thread = make_thread(info, philos, mutex);
	if (!philos || !thread)
	{
		all_free(&info, mutex, philos, thread);
		return (1);
	}
	while (1)
		if (monitor(info, philos))
			break ;
	destruct(&info, thread, philos, mutex);
	return (0);
}

bool	philo_status(t_info info, t_philos *philo, bool *finished)
{
	struct timeval	tp;
	bool			flag;

	flag = false;
	pthread_mutex_lock(&(philo->status));
	if (!philo->finished)
		(*finished) = false;
	else
	{
		pthread_mutex_unlock(&(philo->status));
		return (flag);
	}
	gettimeofday(&tp, NULL);
	if (((tp.tv_sec) * 1000 + tp.tv_usec / 1000) - ((philo->last_meal.tv_sec)
			* 1000 + (philo->last_meal.tv_usec) / 1000) > info.time_to_die)
		flag = true;
	pthread_mutex_unlock(&(philo->status));
	return (flag);
}

int	monitor(t_info info, t_philos *philos)
{
	int		i;
	bool	finished;

	i = 0;
	finished = true;
	while (i < info.num_of_philos)
	{
		if (philo_status(info, &(philos[i]), &finished))
		{
			set_philo_dead((philos[i]));
			return (1);
		}
		i++;
	}
	usleep(500);
	return (finished);
}

void	destruct(t_info *info, pthread_t *thread, t_philos *philos,
		pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	i = 0;
	while (i < info->num_of_philos)
	{
		pthread_mutex_destroy(&(mutex[i]));
		pthread_mutex_destroy(&(philos[i].status));
		i++;
	}
	all_free(info, mutex, philos, thread);
}

/*
#include <libc.h>

__attribute__((destructor))
static void	destructor(void) {
    system("leaks -q philo");
}
*/
