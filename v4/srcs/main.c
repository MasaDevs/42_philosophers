/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masahito <masahito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:15:36 by marai             #+#    #+#             */
/*   Updated: 2023/06/19 11:21:57 by masahito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int			monitor(t_info info, t_philos *philos);
void		destruct(const t_info info, pthread_t *thread, t_philos *philos,
				pthread_mutex_t *mutex);

int	main(int argc, char *argv[])
{
	t_info			info;
	t_philos		*philos;
	pthread_mutex_t	dead;
	pthread_mutex_t	*mutex;
	pthread_t		*thread;

	if (argc < 5 || 6 < argc)
		return (0);
	pthread_mutex_init(&dead, NULL);
	set_info(&info, argc, argv);
	mutex = make_mutex(info);
	philos = make_philos(info, mutex, &dead);
	thread = make_thread(info, philos);
	while (1)
		if (monitor(info, philos))
			break ;
	destruct(info, thread, philos, mutex);
	free(thread);
	free(philos);
	free(mutex);
	return (1);
}


int	monitor(t_info info, t_philos *philos)
{
	struct timeval	tp;
	int				flag;
	int				i;
	bool			finished;

	flag = 0;
	i = 0;
	finished = true;
	while (i < info.num_of_philos)
	{
		pthread_mutex_lock(&(philos[i].status));
		if(!philos[i].finished)
			finished = false;
		else
		{
			pthread_mutex_unlock(&(philos[i].status));
			i++;
			continue ;
		}
		gettimeofday(&tp, NULL);
		if (((tp.tv_sec) * 1000 + tp.tv_usec / 1000)
			- ((philos[i].last_meal.tv_sec) * 1000
				+ (philos[i].last_meal.tv_usec) / 1000) > info.time_to_die)
			flag = 1;
		pthread_mutex_unlock(&(philos[i].status));
		if (flag)
			break ;
		i++;
	}
	if (flag)
	{
		print_philos((philos[i]), "died");
		set_philo_dead((philos[i]));
	}
	if(flag || finished)
		return (1);
	else
		return (0);
}

void	destruct(const t_info info, pthread_t *thread, t_philos *philos,
		pthread_mutex_t *mutex)
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
	free(info.someone_dead);
}

/*
#include <libc.h>

__attribute__((destructor))
static void	destructor(void) {
    system("leaks -q a.out");
}
*/
//malloc
//mutex
//thread
//philos
