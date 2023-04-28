/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayan <mayan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:54:34 by mayan             #+#    #+#             */
/*   Updated: 2023/04/12 17:09:38 by mayan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send(int pid, char c)
{
	int	i;

	i = 0;
	while (i <= 7)
	{
		if ((c & (1 << i)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep (150);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
		{
			send(pid, argv[2][i]);
			i++;
		}
		send(pid, '\n');
	}
	else
	{
		write (1, "\033[91mError: wrong format.\033[0m\n", 31);
		write (1, "\033[33mTry: ./client [PID] [" "MESSAGE" "]\033[0m\n", 40);
		return (1);
	}
	return (0);
}
