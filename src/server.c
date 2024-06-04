/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:35:50 by irsander          #+#    #+#             */
/*   Updated: 2024/06/04 12:08:45 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

t_vec	g_str;

void	ft_error(char *msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	write_and_free(void)
{
	write(1, g_str.data, g_str.length);
	free(g_str.data);
	g_str = (t_vec){0};
}

static void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	static char	c = 0;
	static int	received_signals = 0;

	(void)ucontext;
	if (g_str.alloc_size == 0)
		vec_init(&g_str, 10);
	if (sig == SIGUSR1)
		received_signals++;
	if (sig == SIGUSR2)
	{
		c = c | (1 << received_signals);
		received_signals++;
	}
	if (received_signals == 8)
	{
		vec_push(&g_str, c);
		if (c == '\0')
			write_and_free();
		received_signals = 0;
		c = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_error("failed response");
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	pid = getpid();
	g_str.length = 0;
	ft_printf("pid = %i\n", pid);
	if (sigaction(SIGUSR1, &sa, 0) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, 0) == -1)
		return (1);
	while (1)
		pause();
	free(g_str.data);
	return (0);
}
