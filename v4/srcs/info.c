/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masahito <masahito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:16:13 by marai             #+#    #+#             */
/*   Updated: 2023/06/20 13:51:42 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	set_info(t_info *info, int argc, char *argv[])
{
	if (!is_all_digit(argc, argv))
		err_exit("the arguments should be number\n");
	info->num_of_philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->num_of_eat = ft_atoi(argv[5]);
	else
		info->num_of_eat = -1;
	info->someone_dead = malloc(sizeof(bool));
	if (!info->someone_dead)
		err_exit("malloc error\n");
	*(info->someone_dead) = false;
	if (200 < info->num_of_philos)
	{
		free(info->someone_dead);
		err_exit("the num of philos must be under 200\n");
	}
	return (true);
}

pthread_mutex_t	*make_mutex(const t_info info)
{
	pthread_mutex_t	*mutex;
	int				i;

	mutex = malloc(sizeof(pthread_mutex_t) * info.num_of_philos);
	if (!mutex)
	{
		free(info.someone_dead);
		err_exit("malloc error\n");
	}
	i = 0;
	while (i < info.num_of_philos)
	{
		if (pthread_mutex_init(&(mutex[i]), NULL) != 0)
		{
			free(info.someone_dead);
			err_exit("mutex error\n");
		}
		i++;
	}
	return (mutex);
}

pthread_t	*make_thread(t_info info, t_philos *philos, pthread_mutex_t *mutex)
{
	pthread_t	*thread;
	int			i;

	thread = malloc(sizeof(pthread_t) * info.num_of_philos);
	if (!thread)
	{
		all_free(info, mutex, philos, NULL);
		err_exit("malloc error\n");
	}
	i = 0;
	while (i < info.num_of_philos)
	{
		pthread_create(&(thread[i]), NULL, alloc, (void *)&(philos[i]));
		i++;
	}
	return (thread);
}

void	*alloc(void *philos)
{
	t_philos	*philo;

	philo = (t_philos *)philos;
	if (philo->philos_id % 2)
		odd_philo_meal(philo);
	else
		even_philo_meal(philo);
	return (NULL);
}
