/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:59:42 by idakhlao          #+#    #+#             */
/*   Updated: 2024/12/12 19:02:55 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	loop_monitor(t_data *data, int i)
{
	long	current_time;
	long	last_ate;

	if (data->nb_eat != -1 && data->philo[i].ate >= data->nb_eat)
		return (-1);
	pthread_mutex_lock(&data->philo[i].last_ate_mutex);
	last_ate = data->philo[i].last_ate;
	pthread_mutex_unlock(&data->philo[i].last_ate_mutex);
	current_time = get_time() - data->start;
	if (current_time - last_ate > data->die)
	{
		pthread_mutex_lock(&data->mutex_alive);
		if (data->is_alive)
		{
			data->is_alive = 0;
			pthread_mutex_unlock(&data->mutex_alive);
			pthread_mutex_lock(&data->print_mutex);
			printf("%ld %d died\n", current_time, data->philo[i].index + 1);
			pthread_mutex_unlock(&data->print_mutex);
		}
		else
			pthread_mutex_unlock(&data->mutex_alive);
		return (-1);
	}
	return (0);
}

void	*monitor_philosophers(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->mutex_alive);
		if (!data->is_alive)
		{
			pthread_mutex_unlock(&data->mutex_alive);
			break ;
		}
		pthread_mutex_unlock(&data->mutex_alive);
		i = 0;
		while (i < data->nb_philo)
		{
			if (loop_monitor(data, i) == -1)
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
