/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:21:19 by dsiroten          #+#    #+#             */
/*   Updated: 2024/12/19 15:54:56 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	is_within_limits(char c, long result, int m)
{
	if (result * m > INT_MAX / 10 || (result * m == (INT_MAX / 10)
			&& (c - '0') > (INT_MAX % 10)))
		return (0);
	if (result * m < INT_MIN / 10 || (result * m == (INT_MIN / 10)
			&& (c - '0') * m < (INT_MIN % 10)))
		return (0);
	return (1);
}

int	my_atoi(const char *str)
{
	int			i;
	long		result;
	int			m;

	i = 0;
	result = 0;
	m = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			m *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (!is_within_limits(str[i], result, m))
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (result * m);
}

int	my_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long int time_in_microseconds)
{
	long int	start;
	long int	current;

	start = get_current_time() * 1000;
	current = start;
	while ((current - start) < time_in_microseconds)
	{
		usleep(100);
		current = get_current_time() * 1000;
	}
}


