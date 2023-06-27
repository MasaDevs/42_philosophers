/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:15:58 by marai             #+#    #+#             */
/*   Updated: 2023/06/28 08:22:48 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philos	*make_philos(const t_info info, pthread_mutex_t *mutex,
		pthread_mutex_t *dead)
{
	t_philos	*philos;
	int			i;

	i = 0;
	philos = malloc(sizeof(t_philos) * info.num_of_philos);
	if (!philos)
		return (NULL);
	while (i < info.num_of_philos)
	{
		philos[i].philos_id = i;
		philos[i].num_of_philos = info.num_of_philos;
		philos[i].time_to_eat = info.time_to_eat;
		philos[i].time_to_sleep = info.time_to_sleep;
		philos[i].num_of_eat = info.num_of_eat;
		gettimeofday(&(philos[i].last_meal), NULL);
		philos[i].dead = dead;
		philos[i].finished = false;
		philos[i].someone_dead = info.someone_dead;
		pthread_mutex_init(&(philos[i].status), NULL);
		philos[i].right_hand = &(mutex[i]);
		philos[i].left_hand = &(mutex[(i + 1) % info.num_of_philos]);
		i++;
	}
	return (philos);
}

void	xusleep(t_philos *philo, int time)
{
	struct timeval	tp1;
	struct timeval	tp2;

	if (is_philo_dead(philo))
		return ;
	gettimeofday(&tp1, NULL);
	gettimeofday(&tp2, NULL);
	while ((tp2.tv_sec * 1000000 + tp2.tv_usec) - (tp1.tv_sec * 1000000
			+ tp1.tv_usec) < time)
	{
		usleep(100);
		gettimeofday(&tp2, NULL);
	}
}

void	only_one_philo(t_philos *philo)
{
	if (is_philo_dead(philo))
		return ;
	pthread_mutex_lock(philo->left_hand);
	print_philos(philo, "has taken a fork");
	while (!is_philo_dead(philo))
		;
	pthread_mutex_unlock(philo->left_hand);
	return ;
}

void	odd_philo_meal(t_philos *philo)
{
	int	i;

	i = 0;
	while (i < get_num_of_eat(philo) || get_num_of_eat(philo) < 0)
	{
		if (is_philo_dead(philo))
			return ;
		pthread_mutex_lock(philo->right_hand);
		print_philos(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_hand);
		change_last_meal(philo);
		xusleep(philo, philo->time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_hand);
		pthread_mutex_unlock(philo->left_hand);
		print_philos(philo, "is sleeping");
		xusleep(philo, philo->time_to_sleep * 1000);
		if (0 < get_num_of_eat(philo))
			i++;
		if (get_num_of_eat(philo) == i)
			break ;
		print_philos(philo, "is thinking");
		usleep(200);
	}
	set_finished(philo);
}

void	even_philo_meal(t_philos *philo)
{
	int	i;

	i = 0;
	while (i < get_num_of_eat(philo) || get_num_of_eat(philo) < 0)
	{
		if (is_philo_dead(philo))
			return ;
		pthread_mutex_lock(philo->left_hand);
		print_philos(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_hand);
		change_last_meal(philo);
		xusleep(philo, philo->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_hand);
		pthread_mutex_unlock(philo->right_hand);
		print_philos(philo, "is sleeping");
		xusleep(philo, philo->time_to_sleep * 1000);
		if (0 < get_num_of_eat(philo))
			i++;
		if (get_num_of_eat(philo) == i)
			break ;
		print_philos(philo, "is thinking");
		usleep(200);
	}
	set_finished(philo);
}
