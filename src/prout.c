/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:37:19 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/19 19:12:45 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	init_structure(char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->die = ft_atoi(av[2]);
	data->eat = ft_atoi(av[3]);
	data->sleep = ft_atoi(av[4]);
	if (av[5])
		data->nb_eat = ft_atoi(av[5]);
	else
		data->nb_eat = -1;
	data->start = get_time();
}

void	check_death(t_philo *philo)
{
	long current_time;

	current_time = get_time() - philo->data->start;
	if (current_time - philo->last_ate > philo->data->die)
	{
		current_time = get_time() - philo->data->start;
		printf("%ld %d died\n", current_time, philo->index + 1);
		exit(0);
	}
}

void	*test(void *arg)
{
	t_philo		*philo;
	long		current_time;

	philo = (t_philo *)arg;
	if (philo->index % 2 != 0)
		usleep(100);
	current_time = get_time() - philo->data->start;
	while (1)
	{
		check_death(philo);
		if (philo->index % 2 == 0)
		{
			pthread_mutex_lock(&philo->mutex[philo->index]);
			pthread_mutex_lock(&philo->mutex[(philo->index + 1) % philo->data->nb_philo]);
		}
		else
		{
			pthread_mutex_lock(&philo->mutex[(philo->index + 1) % philo->data->nb_philo]);
			pthread_mutex_lock(&philo->mutex[philo->index]);
		}
		current_time = get_time() - philo->data->start;
		printf("%ld %d is eating\n", current_time, philo->index + 1);
		usleep(philo->data->eat * 1000);
		philo->last_ate = get_time();
		pthread_mutex_unlock(&philo->mutex[philo->index]);
		pthread_mutex_unlock(&philo->mutex[(philo->index + 1) % philo->data->nb_philo]);
		check_death(philo);
		current_time = get_time() - philo->data->start;
		printf("%ld %d is sleeping\n", current_time, philo->index + 1);
		usleep(philo->data->sleep * 1000);
		check_death(philo);
		current_time = get_time() - philo->data->start;
		printf("%ld %d is thinking\n", current_time, philo->index + 1);
	}
	return (NULL);
}

int	init_thread(t_data *data)
{
	pthread_t		*thread;
	pthread_mutex_t	*mutex;
	t_philo			*args;
	int				i;

	thread = malloc(sizeof(pthread_t) * data->nb_philo);
	mutex = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	args = malloc(sizeof(t_philo) * data->nb_philo);
	if (!thread || !args || !mutex)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&mutex[i], NULL);
		args[i].data = data;
		args[i].index = i;
		args[i].mutex = mutex;
		args[i].ate = 0;
		args[i].last_ate = 0;
		if (pthread_create(&thread[i], NULL, &test, &args[i]) != 0)
			return (free(thread), free(mutex), free(args), 1);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(thread[i], NULL);
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
	return (free(thread), free(mutex), free(args), 0);
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
