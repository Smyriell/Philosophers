/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 18:32:49 by smyriell          #+#    #+#             */
/*   Updated: 2021/08/09 18:51:57 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_strlen(char *str)
{
	int	i;
	
	i = -1;
	while (str[++i])
		;
	return (i);
}

int		ft_is_digit(char **arr)
{
	int i;
	int j;

	i = 1;
	while (arr[i])
	{
		j = -1;
		while (arr[i][++j])
		{
			if (j == 0 && arr[i][j] == '-')
				return (ft_str_error("Error! There are only positiv numbers are avaliable\n"));
			if (arr[i][j] < '0' || arr[i][j] > '9')
				return (ft_str_error("Error! There are only digits are avaliable\n"));
		}
		if ((i == 1 && ft_atoi(arr[i]) == -1) || (i > 1 && ft_atoi_long(arr[i]) == -1))
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *s)
{
	int	i;
	unsigned int	numb;

	i = 0;
	numb = 0;
	while (s[i] >= 48 && s[i] <= 57)
	{
		numb = numb * 10 + s[i] - 48;
		i++;
	}
	if (numb > 2147483647)
	{
		ft_str_error("Error! An overflow in arguments\n");
		return (-1);
	}
	else
		return (numb);
}

long long	ft_atoi_long(const char *s)
{
	int					i;
	unsigned long long	numb;

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

