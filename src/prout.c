/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:37:19 by idakhlao          #+#    #+#             */
/*   Updated: 2024/12/03 17:58:00 by idakhlao         ###   ########.fr       */
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
	int	i;

	data->nb_philo = ft_atoi(av[1]);
	data->die = ft_atoi(av[2]);
	data->eat = ft_atoi(av[3]);
	data->sleep = ft_atoi(av[4]);
	if (av[5])
		data->nb_eat = ft_atoi(av[5]);
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
		exit(1);
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	print_status(t_philo *philo, int philo_id, char *status)
{
	long	time;

	time = get_time() - philo->data->start;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d %s\n", time, philo_id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	check_death(t_philo *philo)
{
	long	current_time;

	pthread_mutex_lock(&philo->data->mutex_alive);
	if (!philo->data->is_alive)
	{
		pthread_mutex_unlock(&philo->data->mutex_alive);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->mutex_alive);
	current_time = get_time() - philo->data->start;
	if (current_time - philo->last_ate > philo->data->die)
	{
		pthread_mutex_lock(&philo->data->mutex_alive);
		philo->data->is_alive = 0;
		pthread_mutex_unlock(&philo->data->mutex_alive);
		print_status(philo, philo->index + 1, "died");
		return (-1);
	}
	return (0);
}

void	precise_sleep(long sleep_duration, t_philo *philo)
{
	long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) * 1000 < sleep_duration)
	{
		if (check_death(philo) == -1)
			break ;
		usleep(500);
	}
}


void	take_forks(t_philo *philo)
{
	int		left_fork;
	int		right_fork;

	left_fork = philo->index;
	right_fork = (philo->index + 1) % philo->data->nb_philo;
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		print_status(philo, philo->index + 1, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[right_fork]);
		print_status(philo, philo->index + 1, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[right_fork]);
		print_status(philo, philo->index + 1, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		print_status(philo, philo->index + 1, "has taken a fork");
	}
}

void	release_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->index;
	right_fork = (philo->index + 1) % philo->data->nb_philo;
	pthread_mutex_unlock(&philo->data->forks[left_fork]);
	pthread_mutex_unlock(&philo->data->forks[right_fork]);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	print_status(philo, philo->index + 1, "is thinking");
	if (philo->index % 2 != 0)
		usleep(100);
	while (1)
	{
		if (check_death(philo) == -1)
		{
			print_status(philo, philo->index + 1, "died");
			return (NULL);
		}
		take_forks(philo);
		if (check_death(philo) == -1)
		{
			release_forks(philo);
			print_status(philo, philo->index + 1, "died");
			return (NULL);
		}
		print_status(philo, philo->index + 1, "is eating");
		precise_sleep(philo->data->eat * 1000, philo);
		pthread_mutex_lock(&philo->mutex);
		philo->ate++;
		philo->last_ate = get_time() - philo->data->start;
		pthread_mutex_unlock(&philo->mutex);
		release_forks(philo);
		if (philo->data->nb_eat != -1 && philo->ate >= philo->data->nb_eat)
		{
			print_status(philo, philo->index + 1, "is thinking");
			return (NULL);
		}
		if (check_death(philo) == -1)
		{
			print_status(philo, philo->index + 1, "died");
			return (NULL);
		}
		print_status(philo, philo->index + 1, "is sleeping");
		precise_sleep(philo->data->sleep * 1000, philo);
	}
	return (NULL);
}

int	init_thread(t_data *data)
{
	pthread_t		*thread;
	t_philo			*philo;
	int				i;

	thread = malloc(sizeof(pthread_t) * data->nb_philo);
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!thread || !philo)
		return (1);
	i = 0;
	while (i < data->nb_philo)
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
			return (free(thread), free(philo), 1);
		}
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].mutex);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->mutex_alive);
	return (free(thread), free(philo), free(data->forks), 0);
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
	t_data	data;

	if (parsing(ac, av) == -1)
		return (printf("Error\n"), 0);
	init_structure(av, &data);
	init_thread(&data);
	return (0);
}
