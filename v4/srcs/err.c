#include "../includes/philo.h"
#include <stdlib.h>
bool	is_all_digit(char argc, char *argv[])
{
	int		i;
	int		j;

	i = 1;
	while(i < argc)
	{
		j = 0;
		while(argv && argv[i] && argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	err_massage(char *str)
{
	if(str)
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
