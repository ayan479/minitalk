/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayan <mayan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:54:37 by mayan             #+#    #+#             */
/*   Updated: 2023/04/08 17:41:26 by mayan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	receive(int sig)
{
	static char	c;
	static int	i;

	if (sig == SIGUSR1)
		c = c | (1 << i);
	i++;
	if (i == 8)
	{
		ft_putchar_fd(c, 1);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	write(1, "PID: ", 5);
	ft_putnbr_fd(getpid(), 1);
	write (1, "\n", 2);
	write(1, "\033[90mWaiting for a message...\033[0m\n", 35);
	signal(SIGUSR1, receive);
	signal(SIGUSR2, receive);
	while (1)
		pause();
	return (0);
}
