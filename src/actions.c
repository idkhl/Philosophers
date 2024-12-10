/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:49:37 by idakhlao          #+#    #+#             */
/*   Updated: 2024/12/10 15:50:38 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
		printf("%ld %d died\n", current_time, philo->index + 1);
		pthread_mutex_unlock(&philo->data->mutex_alive);
		return (-1);
	}
	return (0);
}

void	print_status(t_philo *philo, int philo_id, char *status)
{
	long	time;

	time = get_time() - philo->data->start;
	pthread_mutex_lock(&philo->data->print_mutex);
	if (check_death(philo) == 0)
		printf("%ld %d %s\n", time, philo_id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	precise_sleep(long sleep_duration, t_philo *philo)
{
	long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) * 1000 < sleep_duration)
	{
		if (check_death(philo) == -1)
			break ;
		pthread_mutex_lock(&philo->data->mutex_alive);
		if (philo->data->is_alive == 0)
		{
			pthread_mutex_unlock(&philo->data->mutex_alive);
			break ;
		}
		pthread_mutex_unlock(&philo->data->mutex_alive);
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
