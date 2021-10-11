/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:11:02 by hde-camp          #+#    #+#             */
/*   Updated: 2021/10/11 17:34:45 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<minitalk.h>
#include	<signal.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>

static void	sig_handler(int signo, siginfo_t *info, void *context)
{
	static t_conn_data	conn_state = {0, 0, 7, 31, NULL};

	(void)context;
	if (conn_state.size_index >= 0)
	{
		msg_size_handler(&conn_state, signo);
	}
	else
	{
		msg_content_handler(&conn_state, signo);
	}
	kill(info->si_pid, SIGUSR1);
}

static void	set_listeners(void)
{
	struct sigaction	act;

	sigaction(SIGUSR1, NULL, &act);
	act.sa_flags = 0 | SA_SIGINFO | SA_NODEFER;
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}

static void	print_pid(int pid)
{
	char	*ptr;

	ptr = ft_itoa(pid);
	ft_putstr_fd("My pid is [", 1);
	ft_putstr_fd(ptr, 1);
	ft_putstr_fd("]\n", 1);
	free(ptr);
}

int	main(void)
{
	print_pid(getpid());
	set_listeners();
	while (1)
		pause();
	return (0);
}
