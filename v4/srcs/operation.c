/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:15:44 by marai             #+#    #+#             */
/*   Updated: 2023/06/22 10:12:47 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	is_philo_dead(t_philos philo)
{
	bool	flag;

	flag = false;
	while (pthread_mutex_lock(philo.dead) != 0)
		;
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

	while (pthread_mutex_lock(philo.dead) != 0)
		;
	gettimeofday(&tp, NULL);
	printf("%ld %d %s\n", tp.tv_sec * 1000 + tp.tv_usec / 1000, philo.philos_id
		+ 1, "died");
	*(philo.someone_dead) = true;
	pthread_mutex_unlock(philo.dead);
}

void	change_last_meal(t_philos *philo)
{
	while (pthread_mutex_lock(&(philo->status)) != 0)
		;
	gettimeofday(&(philo->last_meal), NULL);
	pthread_mutex_unlock(&(philo->status));
}

void	set_finished(t_philos *philo)
{
	while (pthread_mutex_lock(&(philo->status)) != 0)
		;
	philo->finished = true;
	pthread_mutex_unlock(&(philo->status));
}

void	print_philos(t_philos philo, char *str)
{
	struct timeval	tp;
	bool			dead;

	while (pthread_mutex_lock(philo.dead) != 0)
		;
	dead = *(philo.someone_dead);
	pthread_mutex_unlock(philo.dead);
	if (dead)
		return ;
	gettimeofday(&tp, NULL);
	printf("%ld %d %s\n", tp.tv_sec * 1000 + tp.tv_usec / 1000, philo.philos_id
		+ 1, str);
}
