/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:35:48 by irsander          #+#    #+#             */
/*   Updated: 2024/06/04 12:14:36 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

bool	g_received;

void	ft_error(char *msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static void	send_signal(int server_pid, char c)
{
	static int	bits = 0;
	int			error;

	error = 0;
	while (bits < 8)
	{
		if (c & (1 << bits))
			error = kill(server_pid, SIGUSR2);
		else
			error = kill(server_pid, SIGUSR1);
		if (error != 0)
			ft_error("failed to send signal");
		while (!g_received)
			;
		g_received = false;
		usleep(10);
		bits++;
	}
	bits = 0;
}

static void	sig_handler(int signal)
{
	if (signal == SIGUSR1)
		g_received = true;
}

int	main(int argc, char **argv)
{
	int					server_pid;
	int					i;
	struct sigaction	sig;

	i = 0;
	sig.sa_handler = sig_handler;
	sig.sa_flags = 0;
	sigaction(SIGUSR1, &sig, NULL);
	if (argc < 3)
		ft_error("invalid arguments");
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		ft_error("invalid pid");
	while (argv[2][i])
	{
		g_received = false;
		send_signal(server_pid, argv[2][i]);
		i++;
	}
	g_received = false;
	send_signal(server_pid, '\0');
	return (0);
}
