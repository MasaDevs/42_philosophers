/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 05:35:39 by marai             #+#    #+#             */
/*   Updated: 2023/06/28 10:35:02 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_status(t_info info, t_philos *philo, bool *finished)
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
			set_philo_dead(&(philos[i]));
			return (1);
		}
		i++;
	}
	usleep(300);
	return (finished);
}
