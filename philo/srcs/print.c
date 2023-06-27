/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 10:21:13 by marai             #+#    #+#             */
/*   Updated: 2023/06/28 07:13:28 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philos(t_philos *philo, char *str)
{
	struct timeval	tp;
	bool			dead;

	gettimeofday(&tp, NULL);
	pthread_mutex_lock(philo->dead);
	dead = *(philo->someone_dead);
	if (dead)
	{
		pthread_mutex_unlock(philo->dead);
		return ;
	}
	printf("%ld %d %s\n", tp.tv_sec * 1000 + tp.tv_usec / 1000, philo->philos_id
		+ 1, str);
	pthread_mutex_unlock(philo->dead);
}

void	print_philos_eat(t_philos *philo, char *str, struct timeval tp)
{
	bool			dead;

	pthread_mutex_lock(philo->dead);
	dead = *(philo->someone_dead);
	if (dead)
	{
		pthread_mutex_unlock(philo->dead);
		return ;
	}
	printf("%ld %d %s\n", tp.tv_sec * 1000 + tp.tv_usec / 1000, philo->philos_id
		+ 1, str);
	pthread_mutex_unlock(philo->dead);
}
