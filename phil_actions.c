/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 00:08:56 by smyriell          #+#    #+#             */
/*   Updated: 2021/08/05 21:50:14 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int    phil_eat(t_phil *one_phil)
{
    if (one_phil->numb_of_meal == one_phil->input_data->times_to_eat_optional)
        return (1);
    if (one_phil->id % 2 != 0)
    {
        pthread_mutex_lock(&one_phil->input_data->forks[one_phil->left_fork]);
        action_data_output(one_phil, "has taken a left fork\n");
        pthread_mutex_lock(&one_phil->input_data->forks[one_phil->right_fork]);
        action_data_output(one_phil, "has taken a right fork\n");
        one_phil->numb_of_meal++;
        action_data_output(one_phil, "is eating\n");
		usleep(one_phil->input_data->eating_time * 1000);
        pthread_mutex_unlock(&one_phil->input_data->forks[one_phil->left_fork]);
        pthread_mutex_unlock(&one_phil->input_data->forks[one_phil->right_fork]);
    }
    else
    {
        pthread_mutex_lock(&one_phil->input_data->forks[one_phil->right_fork]);
        action_data_output(one_phil, "has taken a right fork\n");
        pthread_mutex_lock(&one_phil->input_data->forks[one_phil->left_fork]);
        action_data_output(one_phil, "has taken a left fork\n");
        // one_phil->finished = get_time();
        one_phil->numb_of_meal++;
        action_data_output(one_phil, "is eating\n");
		usleep(one_phil->input_data->eating_time * 1000);
        pthread_mutex_unlock(&one_phil->input_data->forks[one_phil->right_fork]);
        pthread_mutex_unlock(&one_phil->input_data->forks[one_phil->left_fork]);
    }
    return (0);
}

void    action_data_output(t_phil *one_phil, char *message)
{
    long long	action_time;

	action_time = get_time() - one_phil->begin;
	printf("%lld [%d] Philo %s\n", action_time, one_phil->id + 1, message);
}

int	check_dead_phil(t_data *input_data)
{
    int i;
    long long timer;

    timer = get_time();

    i = -1;
    while (++i < input_data->philo_nbr)
    {
        if ((timer - input_data->one_phil[i].finished) > \
                                                    input_data->time_to_die)
        {
            action_data_output(&input_data->one_phil[i], "starved to death\n");
            input_data->one_phil[i].dead = 1;
			return (1);
        }
    }
    return (0);
}

int each_phil_fullfed(t_data *input_data)
{
    int i;
    int full_phil;

    i = -1;
    full_phil = 0;
    while (++i < input_data->philo_nbr)
    {
        if (input_data->one_phil[i].numb_of_meal == input_data->times_to_eat_optional)
            full_phil++;
    }
    if (full_phil == input_data->philo_nbr)
        return (1);
    else
    {
        return (0);
    }
}

// сделать мьютекс на вывод сообщений, напиши функцию для этого: лок, прин, анлок

