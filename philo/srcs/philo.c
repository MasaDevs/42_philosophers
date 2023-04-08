#include "../includes/philo.h"

int main(int argc, char *argv[])
{
	int	num_of_people;
	int	*philosophers;
	(void) argc;

	num_of_people = atoi(argv[1]);
	philosophers = malloc(sizeof(int) * num_of_people);
	if(!philosophers)
		return (1);
	return 0;
}