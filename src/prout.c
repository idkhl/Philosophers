/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:37:19 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/15 18:10:18 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_structure(char **av, t_data *philo)
{
	philo->nb_philo = ft_atoi(av[1]);
	philo->die = ft_atoi(av[2]);
	philo->eat = ft_atoi(av[3]);
	philo->sleep = ft_atoi(av[4]);
	if (av[5])
		philo->nb_eat = ft_atoi(av[5]);
}

void	*test()
{
	printf("TESTTESTEST\n");
	return (NULL);
}

void	init_thread()
{
	pthread_t thread1, thread2;

	pthread_create(&thread1, NULL, &test, NULL);
	pthread_create(&thread2, NULL, &test, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
}

int	parsing(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (-1);
	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) > 0)
			i++;
		else
			return (-1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	philo;
	// pthread_t thread1, thread2;

	if (parsing(ac, av) == -1)
		return (printf("Error\n"), 0);
	init_structure(av, &philo);
	init_thread();
	return (0);
}
