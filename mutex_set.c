/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 19:06:51 by smyriell          #+#    #+#             */
/*   Updated: 2021/08/08 00:44:46 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_init(t_data *input_data)
{
	int	i;

	input_data->forks = (pthread_mutex_t *)malloc(input_data->philo_nbr * sizeof(pthread_mutex_t));
	if (!input_data->forks)
		return (ft_str_error("Error! Memmory allocation\n"));
	i = -1;
	while (++i < input_data->philo_nbr)
	{
		if (pthread_mutex_init(&input_data->forks[i], NULL))
			return (ft_str_error("Error! Mutex for philo was not inited\n"));
	}
	if (pthread_mutex_init(&input_data->print_lock, NULL))
        return (ft_str_error("Error! Mutex for message printing was not inited\n"));
	return (0);
}

void    phil_eat(t_phil *one_phil)
{
    
    if (one_phil->id == one_phil->input_data->philo_nbr - 1)
    {
        pthread_mutex_lock(&one_phil->input_data->forks[one_phil->right_fork]);
        // print_message(one_phil, "took a right fork\n");
        pthread_mutex_lock(&one_phil->input_data->forks[one_phil->left_fork]);
        // pthread_mutex_lock(&one_phil->input_data->print_lock);
        print_message(one_phil, "took forks\n");
        one_phil->numb_of_meal++;
        print_message(one_phil, "\e[32m is eating\e[39m\n");
        // pthread_mutex_unlock(&one_phil->input_data->print_lock);
		ft_usleep(one_phil->input_data->eating_time);
        pthread_mutex_unlock(&one_phil->input_data->forks[one_phil->right_fork]);
        pthread_mutex_unlock(&one_phil->input_data->forks[one_phil->left_fork]);
    }
    else
    {
        pthread_mutex_lock(&one_phil->input_data->forks[one_phil->left_fork]);
        // print_message(one_phil, "took a left fork\n");
        pthread_mutex_lock(&one_phil->input_data->forks[one_phil->right_fork]);
        // pthread_mutex_lock(&one_phil->input_data->print_lock);
        print_message(one_phil, "took forks\n");
        one_phil->numb_of_meal++;
        print_message(one_phil, "\e[32m is eating\e[39m\n");
        // pthread_mutex_unlock(&one_phil->input_data->print_lock);
		ft_usleep(one_phil->input_data->eating_time);
        pthread_mutex_unlock(&one_phil->input_data->forks[one_phil->right_fork]);
        pthread_mutex_unlock(&one_phil->input_data->forks[one_phil->left_fork]);
    }
    one_phil->time_to_die = get_time() + one_phil->input_data->time_to_die;
    // return (0);
}

void    print_message(t_phil *one_phil, char *str)
{
    // long long	action_time;

	// action_time = get_time() - one_phil->begin;
    pthread_mutex_lock(&one_phil->input_data->print_lock);
	// printf("%lld [%d] Philo %s\n", action_time, one_phil->id + 1, str);
    action_data_output(one_phil, str);
    pthread_mutex_unlock(&one_phil->input_data->print_lock);
}
