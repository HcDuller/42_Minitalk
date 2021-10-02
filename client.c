/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 13:39:49 by hde-camp          #+#    #+#             */
/*   Updated: 2021/10/01 23:31:15 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	signal_handler(int signo, siginfo_t *info, void *context)
{
	write(1, "Recebi uma mensagem\n" , 20);
}

int	main(int argc,char **argv)
{
	int		pid;
	struct	sigaction	act;

	act.sa_sigaction = signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO | SA_NODEFER | SA_RESTART;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	if (argc > 1)
	{
		pid = ft_atoi(argv[1]);
		kill(pid, SIGUSR1);
		pause();
	}
	return (0);
}