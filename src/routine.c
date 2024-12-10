/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:51:38 by idakhlao          #+#    #+#             */
/*   Updated: 2024/12/10 14:02:13 by idakhlao         ###   ########.fr       */
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
	philo->ate++;
	philo->last_ate = get_time() - philo->data->start;
	precise_sleep(philo->data->eat * 1000, philo);
	release_forks(philo);
}

void	sleep_and_think(t_philo *philo)
{
	print_status(philo, philo->index + 1, "is sleeping");
	precise_sleep(philo->data->sleep * 1000, philo);
	print_status(philo, philo->index + 1, "is thinking");
	// printf("TEST\n");
	// if (philo->data->nb_philo % 2 == 0)
	// {
	// precise_sleep(((philo->data->die - philo->data->sleep) / 2) * 1000, philo);
	precise_sleep(1000, philo);
	// }
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
