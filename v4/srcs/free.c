/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 09:40:18 by marai             #+#    #+#             */
/*   Updated: 2023/06/22 09:45:04 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	all_free(t_info *info, pthread_mutex_t *mutex, t_philos *philos,
		pthread_t *thread)
{
	if (info)
		free(info->someone_dead);
	if (mutex)
		free(mutex);
	if (thread)
		free(thread);
	if (philos)
		free(philos);
}
