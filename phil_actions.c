/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 00:08:56 by smyriell          #+#    #+#             */
/*   Updated: 2021/08/08 00:44:07 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    action_data_output(t_phil *one_phil, char *message)
{
    time_t	action_time;

	action_time = get_time() - one_phil->begin;
	printf("%ld [%d] Philo %s", action_time, one_phil->id + 1, message);
}

int	check_dead_phil(t_data *input_data)// вот тут нужно подумать как правильно выставить время!!!
{
    int i;
    long long timer;

    // timer = get_time();

    i = -1;
    while (++i < input_data->philo_nbr)
    {
        // if ((timer - input_data->one_phil[i].finished) > \
        //                                             input_data->time_to_die)
        if (get_time() > input_data->one_phil[i].time_to_die)
        {
            pthread_mutex_lock(&input_data->print_lock);
            action_data_output(&input_data->one_phil[i], "\e[91mstarved to death\e[39m\n");
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
        return (0);
}

// сделать мьютекс на вывод сообщений, напиши функцию для этого: лок, прин, анлок

