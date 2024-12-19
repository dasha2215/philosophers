/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:21:10 by dsiroten          #+#    #+#             */
/*   Updated: 2024/08/26 16:50:20 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	if (!are_args_valid(argc, argv))
		return (1);
	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	if (!init_simulation(table, argc, argv))
		return (1);
	if (!start_simulation(table))
		return (1);
	join_threads(table);
	stop_simulation(table);
	return (0);
}
