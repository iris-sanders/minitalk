/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:35:48 by irsander          #+#    #+#             */
/*   Updated: 2024/05/28 13:54:53 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

bool received;

static void	send_signal(int server_pid, char c)
{
	static int	bits = 0;
	int			error;

	error = 0;
	printf("%c", c);
	while (bits < 8)
	{
		if (c & (1 << bits))
			error = kill(server_pid, SIGUSR2);
		else
			error = kill(server_pid, SIGUSR1);
		if (error != 0)
		{
			ft_printf("Error: failed to send signal\n");
			exit(EXIT_FAILURE);
		}
		// usleep(10);
		while (!received)
			;
		received = false;
		usleep(10);
		bits++;
	}
	bits = 0;
}

static void	sig_handler(int signal) {
	if (signal == SIGUSR1) {
		printf("	resp\n");
		received = true;
	}
}

int	main(int argc, char **argv)
{
	int					server_pid;
	int					i;
	struct	sigaction	sig;

	i = 0;
	sig.sa_handler = sig_handler;
	sig.sa_flags = 0;
	sigaction(SIGUSR1, &sig, NULL);
	if (argc < 3)
	{
		ft_printf("Error: invalid arguments");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_printf("Error: invalid pid");
		return (1);
	}
	while (argv[2][i])
	{
		received = false;
		send_signal(server_pid, argv[2][i]);
		// printf("\nJust sent: %c\n", argv[2][i]);
		i++;
	}
	received = false;
	send_signal(server_pid, '\0');
	return (0);
}
