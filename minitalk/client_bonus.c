/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayan <mayan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:12:16 by mayan             #+#    #+#             */
/*   Updated: 2023/04/10 21:26:08 by mayan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_len;

void	ft_received(int sig)
{
	if (sig == SIGUSR2)
	{
		write(1, "\033[0;32mSERVER : Received  ", 27);
		ft_putnbr_fd(g_len, 1);
		write(1, " character(s).\n\033[0m", 16);
	}
}

void	send(int pid, char c)
{
	int	i;

	i = 0;
	while (i <= 7)
	{
		if ((c & (0x01 << i)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep (200);
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
			signal(SIGUSR1, ft_received);
			signal(SIGUSR2, ft_received);
			send(pid, argv[2][i]);
			i++;
			g_len = i;
		}
		send(pid, '\n');
	}
	else
	{
		write(1, "\033[91mError: wrong format.\033[0m\n", 31);
		write(1, "\033[33mTry: ./client_bonus [PID] [MESSAGE]\033[0m\n", 46);
		return (1);
	}
	return (0);
}
