/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:15:44 by marai             #+#    #+#             */
/*   Updated: 2023/06/28 05:53:23 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_philo_dead(t_philos philo)
{
	bool	flag;

	flag = false;
	pthread_mutex_lock(philo.dead);
	if (*(philo.someone_dead))
		flag = true;
	pthread_mutex_unlock(philo.dead);
	return (flag);
}

int	get_num_of_eat(t_philos philo)
{
	int	num_of_eat;

	num_of_eat = philo.num_of_eat;
	return (num_of_eat);
}

void	set_philo_dead(t_philos philo)
{
	struct timeval	tp;

	pthread_mutex_lock(philo.dead);
	*(philo.someone_dead) = true;
	gettimeofday(&tp, NULL);
	printf("%ld %d %s\n", tp.tv_sec * 1000 + tp.tv_usec / 1000, philo.philos_id
		+ 1, "died");
	pthread_mutex_unlock(philo.dead);
}

void	change_last_meal(t_philos *philo)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	pthread_mutex_lock(&(philo->status));
	philo->last_meal = tp;
	pthread_mutex_unlock(&(philo->status));
	print_philos_eat(*philo, "is eating", tp);
}

void	set_finished(t_philos *philo)
{
	pthread_mutex_lock(&(philo->status));
	philo->finished = true;
	pthread_mutex_unlock(&(philo->status));
}
