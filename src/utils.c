/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:11:29 by idakhlao          #+#    #+#             */
/*   Updated: 2024/12/12 19:02:50 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_atol(char *str)
{
	long long	nb;
	int			neg;

	nb = 0;
	neg = 1;
	if (!str)
		return (0);
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - '0');
		str++;
		if ((nb * neg) > INT_MAX / 1000 || (nb * neg) < INT_MIN)
			return (0);
	}
	if (*str)
		return (0);
	return (nb * neg);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	one_philo(t_philo *philo)
{
	print_status(philo, philo->index + 1, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[0]);
	usleep(philo->data->die * 1000);
	pthread_mutex_unlock(&philo->data->forks[0]);
}

void	destroy_mutexes(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].mutex);
		pthread_mutex_destroy(&philo[i].last_ate_mutex);
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->mutex_alive);
}
