/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:19:06 by smyriell          #+#    #+#             */
/*   Updated: 2021/08/08 00:41:09 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
number_of_philosophers = number_of_forks

number_of_times_each_philosopher_must_eat: argument is optional, if all
philosophers eat at least ’number_of_times_one_philosopher_must_eat’ the
simulation will stop. If not specified, the simulation will stop only at the death
of a philosopher.

time_to_die: : is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’
milliseconds after starting his last meal or the beginning of the simulation, it
dies

time_to_eat: is in milliseconds and is the time it takes for a philosopher to
eat. During that time he will need to keep the two forks

time_to_sleep: is in milliseconds and is the time the philosopher will spend
sleeping.

Philosopher number 1 is next to philosopher number ’number_of_philosophers’.
Any other philosopher with the number N is seated between philosopher N - 1 and
philosopher N + 1

Any change of status of a philosopher must be written as follows (with X replaced
with the philosopher number and timestamp_in_ms the current timestamp in milliseconds)
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died

The status printed should not be scrambled or intertwined with another philosopher’s status.

You can’t have more than 10 ms between the death of a philosopher and when it
will print its death.

philosophers should avoid dying!!!!


Arguments: 
number_of_philosophers 
time_to_die 
time_to_eat
time_to_sleep 
optional: number_of_times_one_philosopher_must_eat


External functs:
memset, 
printf, 
malloc, free, 
write,
usleep, 
gettimeofday, 
- pthread_create создание потока
- pthread_detach(): отключиться от потока, сделав его при этом отдельным (PTHREAD_CREATE_DETACHED), 
- pthread_join (): подключиться к другому потоку и ожидать его завершения, поток, 
к которому необходимо подключиться, должен быть создан с возможностью подключения (PTHREAD_CREATE_JOINABLE), 
- pthread_mutex_init,
- pthread_mutex_destroy, 
- pthread_mutex_lock,
- pthread_mutex_unlock


One fork between one philosopher, therefore if they are multiple philosophers, there
will be a fork at the right and the left of one philosopher.

To avoid philosophers duplicating forks, you should protect the forks state with a
mutex for one of them!

one philosopher should be a thread


Типы данных:
pthread_t: дескриптор потока;
pthread_attr_t: перечень атрибутов потока;
pthread_barrier_t: барьер;
pthread_barrierattr_t: атрибуты барьера;
pthread_cond_t: условная переменная;
pthread_condattr_t: атрибуты условной переменной;
pthread_key_t: данные, специфичные для потока;
pthread_mutex_t: мьютекс;
pthread_mutexattr_t: атрибуты мьютекса;
pthread_rwlock_t: мьютекс с возможностью эксклюзивной блокировки;
pthread_rwlockattr_t: атрибуты этого мьютекса;
pthread_spinlock_t: спинлок;
*/

// void*	test()
// {
// 	printf("Test from thread\n");
// 	sleep(3);
// 	printf("ending\n");
// 	return (0);
// }

// int	main(int argc, char **argv)
// {
//     pthread_t	t1;
// 	pthread_t	t2;
	
// 	if (pthread_create(&t1, NULL, &test, NULL) != 0)
// 		return (1);
// 	if (pthread_create(&t2, NULL, &test, NULL) != 0)
// 		return (2);
// 	if (pthread_join(t1, NULL) != 0)
// 		return (3);
// 	if (pthread_join(t2, NULL) != 0)
// 		return (4);
// 	return (0);
// }

void	*ft_monitor(void *input_data)
{
	t_data	*data_input;

	data_input = (t_data *)input_data;
	while (1)
	{
		if (check_dead_phil(data_input))
			break ;
		if (data_input->times_to_eat_optional != -1 && each_phil_fullfed(data_input))
		{
			pthread_mutex_lock(&data_input->print_lock);
			printf("times to eat for each philo = %d, everybody is full\n", data_input->times_to_eat_optional);
			break ;
		}
	}
	return (NULL);
}

int	ft_data_valid(char **argv)
{
	int			i;
	long long	n;	

	i = 0;
	if (ft_is_digit(argv))
		return (ft_str_error("Invalid format of argument\n"));
	while (argv[++i])
	{
		if (i == 1 || i == 5)
			n = ft_atoi(argv[i]);
		else
			n = ft_atoi_long(argv[i]);
		if (i == 1 && n < 1)
			return (ft_str_error("Error! Invalid number of Philosophers\n"));
		if (n < 60 && (i == 2 || i == 3 || i == 4))
			return (ft_str_error("Error! Invalid time of the action (die, eat, sleep)\n"));
	}
	return (0);
}

void	common_struct_init(char **argv, t_data *input_data)
{
	input_data->philo_nbr = ft_atoi(argv[1]);
	input_data->time_to_die = ft_atoi_long(argv[2]);
	input_data->eating_time = ft_atoi_long(argv[3]);
	input_data->sleeping_time = ft_atoi_long(argv[4]);
	if (argv[5])
		input_data->times_to_eat_optional = ft_atoi(argv[5]);
	else
		input_data->times_to_eat_optional = -1;
	input_data->start_time = get_time();
}

int	each_phil_arr_init(t_data *input_data)
{
	int	i;

	input_data->one_phil = (t_phil *)malloc(input_data->philo_nbr * sizeof(t_phil));
	if (!input_data->one_phil)
		return (ft_str_error("Error! Memmory allocation\n"));
	i = -1;
	while (++i < input_data->philo_nbr)
	{
		input_data->one_phil[i].id = i;
		input_data->one_phil[i].numb_of_meal = 0;
		input_data->one_phil[i].left_fork = i;
		input_data->one_phil[i].right_fork = (i + 1) % input_data->philo_nbr;
		input_data->one_phil[i].dead = 0;
		input_data->one_phil[i].input_data = input_data;
	}
	return (0);
}

int	ft_check_phil_condition(t_phil *one_phil)
{
	if (one_phil->dead)
		return (1);
	if (one_phil->numb_of_meal == one_phil->input_data->times_to_eat_optional)
		return (1);
	return (0);
}

void *ft_launching(void *one_of_philo)
{
	t_phil	*one_phil;
	
	one_phil = (t_phil *)one_of_philo;
	one_phil->begin = get_time();
	one_phil->time_to_die = get_time() + one_phil->input_data->time_to_die;
	while (1)
	{
		if (ft_check_phil_condition(one_phil))
			break;
		phil_eat(one_phil);
		// one_phil->finished = get_time();
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

int	threads(t_data *input_data)
{
	int	i;

	input_data->phil_thread = (pthread_t *)malloc(input_data->philo_nbr * sizeof(pthread_t));
	if (!input_data->phil_thread)
		return (ft_str_error("Error! Memmory allocation\n"));
	i = 0;
	while (i < input_data->philo_nbr)
	{
		if (pthread_create(&input_data->phil_thread[i], NULL, ft_launching, (void *)&input_data->one_phil[i]))
			return (ft_str_error("Error! Thread was not created\n"));
		if (pthread_detach(input_data->phil_thread[i]))
			return (ft_str_error("Error! Thread was not detached\n"));
		i = i + 1;
	}
	return (0);
}

int	start_philo(char **argv)
{
	t_data	*input_data;
	t_phil	*one_phil;
	// int	i;

	if (ft_data_valid(argv))
		return (1);
	input_data = (t_data *)malloc(sizeof(t_data));
	if (!input_data)
		return (ft_str_error("Error! Memmory allocation\n"));
	input_data->monitor_thread = (pthread_t *)malloc(sizeof(pthread_t));// protect
	common_struct_init(argv, input_data);
	if (mutex_init(input_data) || each_phil_arr_init(input_data))
		return (1);
	if (threads(input_data))
		return (1);
	if (pthread_create(input_data->monitor_thread, NULL, ft_monitor, (void *)input_data))
			return (ft_str_error("Error! Monitor_thread was not created\n"));
	pthread_join(*input_data->monitor_thread, NULL);
	printf("!! monitor is finished\n");
	// i = -1;
	// while (i++ < input_data->philo_nbr)
	// 	pthread_mutex_destroy(&input_data->forks[i]);
	pthread_mutex_destroy(&input_data->print_lock);
	// make free of all mallocs and mutex
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (start_philo(argv))
			return (1);
	}
	else
		return (ft_str_error("Error! Wrong number of arguments\n"));
	return (0);
}

// 1. Предполагается, что философ всегда пытается сначала взять левую вилку, а потом — правую (или наоборот), что упрощает логику.
// 2. ресурсы (вилки) будут пронумерованы от 1 до 5, и каждая рабочая единица (философ) всегда берёт сначала вилку с наименьшим номером, а потом вилку с наибольшим номером из двух доступных.
// Далее, философ кладёт сначала вилку с бо́льшим номером, потом — с меньшим.