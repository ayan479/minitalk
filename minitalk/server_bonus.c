/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayan <mayan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:26:40 by mayan             #+#    #+#             */
/*   Updated: 2023/04/08 20:30:27 by mayan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	receive(int sig, siginfo_t *info, void *ptr)
{
	static int	i;
	static char	c;

	(void)info;
	(void)ptr;
	if (sig == SIGUSR1)
		c = c | (1 << i);
	i++;
	if (i == 8)
	{
		write(1, &c, 1);
		i = 0;
		c = 0;
		kill(info->si_pid, SIGUSR2);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argv;
	write(1, "PID: ", 5);
	ft_putnbr_fd(getpid(), 1);
	write (1, "\n", 2);
	write(1, "\033[90mWaiting for a message...\033[0m\n", 35);
	sa.sa_sigaction = receive;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	while (argc == 1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	return (0);
}
