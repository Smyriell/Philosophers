/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 00:08:56 by smyriell          #+#    #+#             */
/*   Updated: 2021/07/31 01:05:05 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void    phil_eat(t_phil *one_phil)
{

    printf("PHILO %d in eat\n", one_phil->id);
    printf("left fork = %d right fork = %d\n", one_phil->left_fork, one_phil->right_fork);
    pthread_mutex_lock(&one_phil->input_data->forks[one_phil->left_fork]);
    action_data_output(one_phil, "has taken a left fork\n");
	pthread_mutex_lock(&one_phil->input_data->forks[one_phil->right_fork]);
    action_data_output(one_phil, "has taken a right fork\n");
	one_phil->finished = get_time();//mili
	one_phil->numb_of_meal++;
    action_data_output(one_phil, "is eating\n");
	usleep(one_phil->input_data->eating_time * 1000);
    pthread_mutex_unlock(&one_phil->input_data->forks[one_phil->left_fork]);
	pthread_mutex_unlock(&one_phil->input_data->forks[one_phil->right_fork]);
}

void    action_data_output(t_phil *one_phil, char *message)
{
    long long	action_time;

	action_time = get_time() - one_phil->begin;
    // printf("action_time = %lld\n", action_time);
	printf("%lld [%d] Philo %s\n", action_time, one_phil->id + 1, message);
}

// void    bury_phil(t_data *input_data)
// {
//     int i;

//     i = -1;
//     while (++i < input_data->philo_nbr)
//         pthread_detach(input_data->phil_thread[i]);
    
// }

int	check_dead_phil(t_data *input_data)
{
    int i;
    long long timer;

    timer = get_time();

    i = -1;
    while (++i < input_data->philo_nbr)
    {
        //  printf("timer = %lld\n", timer);
        //  printf("input_data->one_phil[i].finished = %lld\n", input_data->one_phil[i].finished);
        if ((timer - input_data->one_phil[i].finished) > \
                                                    input_data->time_to_die)
        {
            // input_data->one_phil[i].dead = 1;
            action_data_output(&input_data->one_phil[i], "starved to death\n");
			// bury_phil(input_data);
			// return (1);
			// проверить чтобы не детачил снова тех кто уже умер и нужно убивать всех или одного?
        }
    }
    return (0);//return (1) if is dead
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
    {
        // bury_phil(input_data);
        return (1);
    }
    else
        return (0);
    //return (1) if everybody ate max number
}


