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
