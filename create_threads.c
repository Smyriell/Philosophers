/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 18:24:53 by smyriell          #+#    #+#             */
/*   Updated: 2021/08/09 18:55:20 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	phil_eat(t_phil *one_phil)
{
	if (one_phil->id == one_phil->input_data->philo_nbr - 1)
	{
		pthread_mutex_lock(&one_phil->input_data->forks[one_phil->r_fork]);
		pthread_mutex_lock(&one_phil->input_data->forks[one_phil->l_fork]);
		print_message(one_phil, "took forks\n");
		one_phil->numb_of_meal++;
		print_message(one_phil, "\e[32m is eating\e[39m\n");
		ft_usleep(one_phil->input_data->eating_time);
		pthread_mutex_unlock(&one_phil->input_data->forks[one_phil->r_fork]);
		pthread_mutex_unlock(&one_phil->input_data->forks[one_phil->l_fork]);
	}
	else
	{
		pthread_mutex_lock(&one_phil->input_data->forks[one_phil->l_fork]);
		pthread_mutex_lock(&one_phil->input_data->forks[one_phil->r_fork]);
		print_message(one_phil, "took forks\n");
		one_phil->numb_of_meal++;
		print_message(one_phil, "\e[32m is eating\e[39m\n");
		ft_usleep(one_phil->input_data->eating_time);
		pthread_mutex_unlock(&one_phil->input_data->forks[one_phil->r_fork]);
		pthread_mutex_unlock(&one_phil->input_data->forks[one_phil->l_fork]);
	}
	one_phil->death_time = get_time() + one_phil->input_data->time_to_die;
}

int	ft_check_phil_condition(t_phil *one_phil)
{
	if (one_phil->dead)
		return (1);
	if (one_phil->numb_of_meal == one_phil->input_data->times_to_eat_optional)
		return (1);
	return (0);
}

void	*ft_launching(void *one_of_philo)
{
	t_phil	*one_phil;
	
	one_phil = (t_phil *)one_of_philo;
	one_phil->begin = get_time();
	one_phil->death_time = get_time() + one_phil->input_data->time_to_die;
	while (1)
	{
		if (ft_check_phil_condition(one_phil))
			break;
		phil_eat(one_phil);
		if (ft_check_phil_condition(one_phil))
			break;
		print_message(one_phil, "is sleeping\n");
		ft_usleep(one_phil->input_data->sleeping_time);
		if (ft_check_phil_condition(one_phil))
			break;
		print_message(one_phil, "is thinking\n");
	}
	return (NULL);
}

int	create_threads(t_data *input_data)
{
	int	i;

	input_data->phil_thread = (pthread_t *)malloc(input_data->philo_nbr * \
															sizeof(pthread_t));
	if (!input_data->phil_thread)
		return (ft_str_error("Error! Memmory allocation\n"));
	i = -1;
	while (++i < input_data->philo_nbr)
	{
		if (pthread_create(&input_data->phil_thread[i], NULL, \
							ft_launching, (void *)&input_data->one_phil[i]))
			return (ft_str_error("Error! Thread was not created\n"));
		if (pthread_detach(input_data->phil_thread[i]))
			return (ft_str_error("Error! Thread was not detached\n"));
	}
	if (pthread_create(input_data->monitor_thread, NULL, \
											ft_monitor, (void *)input_data))
			return (ft_str_error("Error! Monitor_thread was not created\n"));
	pthread_join(*input_data->monitor_thread, NULL);
	return (0);
}
