/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:15:44 by marai             #+#    #+#             */
/*   Updated: 2023/06/24 14:33:25 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	pthread_mutex_unlock(philo.dead);
	usleep(2000);
	gettimeofday(&tp, NULL);
	printf("%ld %d %s\n", tp.tv_sec * 1000 + tp.tv_usec / 1000, philo.philos_id
		+ 1, "died");
}

void	change_last_meal(t_philos *philo)
{
	pthread_mutex_lock(&(philo->status));
	gettimeofday(&(philo->last_meal), NULL);
	pthread_mutex_unlock(&(philo->status));
}

void	set_finished(t_philos *philo)
{
	pthread_mutex_lock(&(philo->status));
	philo->finished = true;
	pthread_mutex_unlock(&(philo->status));
}
