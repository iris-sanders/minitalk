/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:35:50 by irsander          #+#    #+#             */
/*   Updated: 2024/05/23 18:21:49 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minitalk.h"

t_vec	str;

static void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	static char	c = 0;
	static int	received_signals = 0;

	if (sig == SIGUSR1)
		received_signals++;
	if (sig == SIGUSR2)
	{
		c = c | (1 << received_signals);
		received_signals++;
	}
	if (received_signals == 8)
	{
		vec_push(&str, c);
		if (c == '\0')
		{
			write(1, str.data, str.length);
			str.length = 0;
		}
		if (kill(info->si_pid, SIGUSR1) == -1)
			exit(1);
		received_signals = 0;
		c = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	vec_init(&str, 10);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	pid = getpid();
	ft_printf("pid = %i\n", pid);
	if (sigaction(SIGUSR1, &sa, 0) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, 0) == -1)
		return (1);
	while (1)
		pause();
	free(str.data);
	return (0);
}
