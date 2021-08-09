/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:36:43 by smyriell          #+#    #+#             */
/*   Updated: 2021/08/09 18:50:47 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long long interval)
{
	time_t			now;
	time_t			stop;

	stop = get_time() + interval;
	now = get_time();
	while (now < stop)
	{
		usleep(50);
		now = get_time();
	}
}

int	ft_str_error(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(2, str, len);
	return (1);
}

void	print_message(t_phil *one_phil, char *str)
{
	pthread_mutex_lock(&one_phil->input_data->print_lock);
	action_data_output(one_phil, str);
	pthread_mutex_unlock(&one_phil->input_data->print_lock);
}

void	action_data_output(t_phil *one_phil, char *message)
{
	time_t	action_time;

	action_time = get_time() - one_phil->begin;
	printf("%ld [%d] Philo %s", action_time, one_phil->id + 1, message);
}
