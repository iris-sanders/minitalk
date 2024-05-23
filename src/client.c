/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:35:48 by irsander          #+#    #+#             */
/*   Updated: 2024/05/23 13:26:02 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
		{
			ft_printf("Error: failed to send signal\n");
			exit(EXIT_FAILURE);
		}
		usleep(80);
		bits++;	
	}
	bits = 0;
}
int	main(int argc, char **argv)
{
	int	server_pid;
	int	i;

	i = 0;
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
	while (argv[2][i] != '\0')
	{
		send_signal(server_pid, argv[2][i]);
		i++;
	}
	return (0);
}
