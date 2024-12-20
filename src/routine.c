/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:51:38 by idakhlao          #+#    #+#             */
/*   Updated: 2024/12/17 12:19:48 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat(t_philo *philo)
{
	take_forks(philo);
	if (check_death(philo) == -1)
	{
		release_forks(philo);
		print_status(philo, philo->index + 1, "died");
		return ;
	}
	print_status(philo, philo->index + 1, "is eating");
	pthread_mutex_lock(&philo->last_ate_mutex);
	philo->last_ate = get_time() - philo->data->start;
	philo->ate++;
	pthread_mutex_unlock(&philo->last_ate_mutex);
	precise_sleep(philo->data->eat * 1000, philo);
	release_forks(philo);
}

void	is_thinking(t_philo *philo)
{
	long	current_time;
	long	time_remaining;

	current_time = get_time() - philo->data->start;
	pthread_mutex_lock(&philo->last_ate_mutex);
	time_remaining = philo->data->die - (current_time - philo->last_ate);
	pthread_mutex_unlock(&philo->last_ate_mutex);
	if (time_remaining > 0)
		precise_sleep((time_remaining / 2) * 1000, philo);
}

void	sleep_and_think(t_philo *philo)
{
	print_status(philo, philo->index + 1, "is sleeping");
	precise_sleep(philo->data->sleep * 1000, philo);
	print_status(philo, philo->index + 1, "is thinking");
	is_thinking(philo);
}

void	loop(t_philo *philo)
{
	while (1)
	{
		if (check_death(philo) == -1)
		{
			print_status(philo, philo->index + 1, "died");
			break ;
		}
		eat(philo);
		if (philo->data->nb_eat != -1 && philo->ate >= philo->data->nb_eat)
			break ;
		if (check_death(philo) == -1)
		{
			print_status(philo, philo->index + 1, "died");
			break ;
		}
		sleep_and_think(philo);
	}
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	print_status(philo, philo->index + 1, "is thinking");
	if (philo->index % 2 != 0)
		precise_sleep(philo->data->eat, philo);
	loop(philo);
	return (NULL);
}
