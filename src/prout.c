/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:37:19 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/18 17:30:21 by idakhlao         ###   ########.fr       */
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

void	*test(void *arg)
{
	t_thread	*data;
	struct timeval	tv;

	data = (t_thread *)arg;
	gettimeofday(&tv, NULL);
	printf("[%ld] Philosopher %d started eating\n", tv.tv_usec, data->index + 1);
	usleep(data->philo->eat);
	printf("[%ld] Philosopher %d finished eating\n", tv.tv_usec, data->index + 1);
	return (NULL);
}

int	init_thread(t_data *philo)
{
	pthread_t	*thread;
	t_thread	*args;
	int			i;

	thread = malloc(sizeof(pthread_t) * philo->nb_philo);
	args = malloc(sizeof(t_thread) * philo->nb_philo);
	if (!thread || !args)
		return (1);
	i = 0;
	while (i < philo->nb_philo)
	{
		args[i].philo = philo;
		args[i].index = i;
		if (pthread_create(&thread[i], NULL, &test, &args[i]) != 0)
		{
			free(thread);
			free(args);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_join(thread[i], NULL))
		{
			free(thread);
			free(args);
			return (1);
		}
		i++;
	}
	free(thread);
	free(args);
	return (0);
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

	if (parsing(ac, av) == -1)
		return (printf("Error\n"), 0);
	init_structure(av, &philo);
	init_thread(&philo);
	return (0);
}
