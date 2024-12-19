/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:21:02 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/10 16:10:01 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	are_args_valid(int argc, char **argv)
{
	int	arg;
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (0);
	while (i < argc)
	{
		arg = my_atoi(argv[i]);
		if (i == 5 && (arg == 0 && my_strcmp(argv[i], "0") != 0))
			return (0);
		if (arg <= 0)
			return (0);
		i++;
	}
	return (1);
}
