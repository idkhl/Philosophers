/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:37:19 by idakhlao          #+#    #+#             */
/*   Updated: 2024/12/10 16:45:44 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_structure(char **av, t_data *data)
{
	int	i;

	data->nb_philo = ft_atol(av[1]);
	data->die = ft_atol(av[2]);
	data->eat = ft_atol(av[3]);
	data->sleep = ft_atol(av[4]);
	if (av[5])
		data->nb_eat = ft_atol(av[5]);
	else
		data->nb_eat = -1;
	data->start = get_time();
	data->is_alive = 1;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->mutex_alive, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
	{
		printf("Error: malloc failed\n");
		return (-1);
	}
	i = 0;
	while (i < data->nb_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	return (0);
}

int	create_threads(t_data *data, t_philo *philo, pthread_t *thread)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		philo[i].data = data;
		philo[i].index = i;
		philo[i].ate = 0;
		philo[i].last_ate = 0;
		pthread_mutex_init(&philo[i].mutex, NULL);
		if (pthread_create(&thread[i], NULL, &routine, &philo[i]) != 0)
		{
			printf("Error: pthread_create failed\n");
			while (--i >= 0)
				pthread_join(thread[i], NULL);
			return (free(data->forks), free(thread), free(philo), -1);
		}
	}
	return (0);
}

void	init_thread(t_data *data)
{
	pthread_t		*thread;
	t_philo			*philo;
	int				i;

	thread = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!thread)
		return (free(data->forks));
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return (free(thread), free(data->forks));
	if (create_threads(data, philo, thread) == -1)
		return ;
	i = -1;
	while (++i < data->nb_philo)
		pthread_join(thread[i], NULL);
	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].mutex);
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->mutex_alive);
	return (free(thread), free(philo), free(data->forks));
}

int	parsing(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (-1);
	i = 1;
	while (av[i])
	{
		if (ft_atol(av[i]) > 0)
			i++;
		else
			return (-1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (parsing(ac, av) == -1)
		return (printf("Error\n"), 0);
	if (init_structure(av, &data) == -1)
		return (0);
	init_thread(&data);
	return (0);
}
