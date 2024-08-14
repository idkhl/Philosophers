/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:37:19 by idakhlao          #+#    #+#             */
/*   Updated: 2024/08/14 19:10:48 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_structure(char **av, t_data *philo)
{
	philo->nb_philo = ft_atoi(av[1]);
	philo->die = ft_atoi(av[2]);
	philo->eat = ft_atoi(av[3]);
	philo->sleep = ft_atoi(av[4]);
	if (av[5])
		philo->nb_eat = ft_atoi(av[5]);
}

void	init_thread(void)
{
	pthread_create();
}

int	parsing(int ac, char **av)
{
	int	i;

	if (ac != 6 || ac != 5)
		return (-1);
	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) > 0)
			i++;
		else
			return (printf("[%s]\n", av[i]), -1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	philo;

	if (parsing(ac, av) == -1)
		return (printf("Error\n"), 0);
	init_structure(av, &philo);
	init_thread();
}
