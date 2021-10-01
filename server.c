/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:35:39 by hde-camp          #+#    #+#             */
/*   Updated: 2021/10/01 18:20:02 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<minitalk.h>
#include	<signal.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>

void	one_handler(int signo, siginfo_t *info, void *context)
{
	static	int	sig_count = 0;
	static	int	total_size = 0;
	

	if (signo == SIGUSR1)
	{
		sig_count += 1;
		if (info->si_pid)
		{
			kill(info->si_pid, SIGUSR1);
		}
	}
	else if (signo == SIGUSR2)
	{
		total_size += 1;
		//push a letter corresponding to sig_count
		ft_putstr_fd("Letter [", 1);
		write(1, &sig_count, 1);
		ft_putstr_fd("] Received\n", 1);
		sig_count = 0;
		if (info->si_pid)
			kill(info->si_pid, SIGUSR2);
	}
		
}

int	main(void)
{
	int		pid;
	char	*pid_as_str;
	struct	sigaction	act;

	act.sa_sigaction = one_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = act.sa_flags | SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	pid = getpid();
	pid_as_str = ft_itoa(pid);
	ft_putstr_fd("PID that i got:", 1);
	ft_putstr_fd(pid_as_str, 1);
	ft_putstr_fd("\n", 1);
	while (1)
		pause();
	free(pid_as_str);
	return (0);
}
