/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:35:50 by irsander          #+#    #+#             */
/*   Updated: 2024/05/23 12:41:19 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	sig_handler(int signal)
{
	static char	bits = 0;
	static int	received_signals = 0;

	if (signal == SIGUSR1)
		received_signals++;
	if (signal == SIGUSR2)
	{
		bits = bits | (1 << received_signals);
		received_signals++;
	}
	if (received_signals == 8)
	{
		write (1, &bits, 1);
		received_signals = 0;
		bits = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sig;

	sig.sa_handler = sig_handler;
	sig.sa_flags = SA_RESTART;
	pid = getpid();
	ft_printf("pid = %i\n", pid);
	sigaction(SIGUSR1, &sig, 0);
	sigaction(SIGUSR2, &sig, 0);
	while (1)
		pause();
}
