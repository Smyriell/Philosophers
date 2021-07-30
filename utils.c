/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:36:43 by smyriell          #+#    #+#             */
/*   Updated: 2021/07/31 00:00:48 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int ft_strlen(char *str)
{
    int i;

    i = -1;
    while (str[++i])
        ;
    return (i);
}

int ft_str_error(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(2, str, len);
	return (1);
}

int		ft_is_digit(char **arr)
{
	int i;
	int j;

	i = 0;

	while (arr[++i])
	{
		j = -1;
		while (arr[i][++j])
		{
			if (arr[i][j] < '0' || arr[i][j] > '9')
				return (ft_str_error("Error! There are only digits are avaliable in arguments\n"));
		}
		if ((int)ft_atoi(arr[i]) == -1)
			return (1);
	}
	return (0);
}

int	ft_atoi(const char *s) // проверить тут что лучше возвращать
{
	int			i;
	long int	numb;

	i = 0;
	numb = 0;
	while (s[i] >= 48 && s[i] <= 57)
	{
		numb = numb * 10 + s[i] - 48;
		i++;
	}
	if (numb > 9223372036854775807)
	{
		ft_str_error("Error! An overflow in arguments\n");
		return (-1);
	}
	else
		return (numb);
}

// void	*ft_calloc(int count, int size)
// {
// 	int		i;
// 	char	*arr;

// 	arr = (void *)malloc(count * size);
// 	if (NULL == arr)
// 		return (NULL);
// 	i = -1;
// 	while (++i < (count * size))
// 		arr[i] = 0;
// 	return (arr);
// }

// int main(int ac, char **av)
// {
	// if (ac == 1)
	// 	return 0;

	// if(ft_is_digit(av))
	// {
	// 	printf("error! \n");
	// }
	// else{
	// 	printf("zaebis\n");
	// }
	

    // str = "apple";
    // printf("i = %d\n", ft_strlen(str));
    // ft_str_error("problem_1");
//     return 0; 
// }

