/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 09:39:54 by marai             #+#    #+#             */
/*   Updated: 2023/06/22 09:39:56 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdlib.h>

bool	err_massage(char *str)
{
	if (str)
	{
		write(2, str, ft_strlen(str));
		return (true);
	}
	return (false);
}

void	err_exit(char *str)
{
	err_massage(str);
	exit(1);
}
