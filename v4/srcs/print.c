/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 10:21:13 by marai             #+#    #+#             */
/*   Updated: 2023/06/22 18:50:04 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_philos(t_philos philo, char *str)
{
	struct timeval	tp;
	bool			dead;

	pthread_mutex_lock(philo.dead);
	dead = *(philo.someone_dead);
	pthread_mutex_unlock(philo.dead);
	if (dead)
		return ;
	gettimeofday(&tp, NULL);
	printf("%ld %d %s\n", tp.tv_sec * 1000 + tp.tv_usec / 1000, philo.philos_id
		+ 1, str);
}
