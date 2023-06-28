/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:16:13 by marai             #+#    #+#             */
/*   Updated: 2023/06/28 12:15:54 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_info_proper(t_info *info)
{
	if (200 < info->num_of_philos || info->num_of_philos < 0)
	{
		err_message("the num of philos should be 0 ~ 200\n");
		return (false);
	}
	if (info->time_to_eat <= 0 || info->time_to_sleep <= 0)
	{
		err_message("time_to_eat and time_to_sleep should be more than 0\n");
		return (false);
	}
	return (true);
}

bool	set_info(t_info *info, int argc, char *argv[])
{
	info->num_of_philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->num_of_eat = ft_atoi(argv[5]);
	else
		info->num_of_eat = -1;
	if (!is_info_proper(info))
		return (false);
	info->someone_dead = malloc(sizeof(bool));
	if (!info->someone_dead)
	{
		err_message("malloc error\n");
		return (false);
	}
	*(info->someone_dead) = false;
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
		err_message("malloc error\n");
		return (NULL);
	}
	i = 0;
	while (i < info.num_of_philos)
	{
		pthread_mutex_init(&(mutex[i]), NULL);
		i++;
	}
	return (mutex);
}

pthread_t	*make_thread(t_info info, t_philos *philos, pthread_mutex_t *mutex)
{
	pthread_t	*thread;
	int			i;

	if (!philos)
		return (NULL);
	thread = malloc(sizeof(pthread_t) * info.num_of_philos);
	if (!thread)
	{
		all_free(&info, mutex, philos, NULL);
		err_message("malloc error\n");
		return (NULL);
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
	int			num_of_philos;
	int			philos_id;

	philo = (t_philos *)philos;
	pthread_mutex_lock(&(philo->status));
	num_of_philos = philo->num_of_philos;
	philos_id = philo->philos_id;
	pthread_mutex_unlock(&(philo->status));
	if (num_of_philos == 1)
		only_one_philo(philo);
	else if (philos_id % 2)
	{
		usleep(200);
		odd_philo_meal(philo);
	}
	else
		even_philo_meal(philo);
	return (NULL);
}
