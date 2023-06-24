/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 09:39:54 by marai             #+#    #+#             */
/*   Updated: 2023/06/25 03:16:53 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

bool	err_message(char *str)
{
	if (str)
	{
		write(2, str, ft_strlen(str));
		return (true);
	}
	return (false);
}

bool	is_arg_correct(int argc, char *argv[])
{
	if (argc < 5 || 6 < argc)
	{
		err_message("the argument should 5 or 6\n");
		return (false);
	}
	if (!is_all_digit(argc, argv))
	{
		err_message("the arguments should be number\n");
		return (false);
	}
	return (true);
}

void	thread_detach(pthread_t *thread, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		pthread_detach(thread[i]);
		i++;
	}
}
