/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:35:39 by hde-camp          #+#    #+#             */
/*   Updated: 2021/10/01 23:34:42 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<minitalk.h>
#include	<signal.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>

void	sig_one_handler(int signo, siginfo_t *info, void *context)
{
	write(1, "Recebi uma mensagem\n" , 20);
	kill(info->pid)
}

void	print_pid(void)
{
	char	*ptr;

	ptr = ft_itoa(getpid());
	ft_putstr_fd("My pid is [", 1);
	ft_putstr_fd(ptr, 1);
	ft_putstr_fd("]\n", 1);
	free(ptr);
}

int	main(void)
{
	struct	sigaction	act;

	act.sa_sigaction = sig_one_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO | SA_NODEFER | SA_RESTART;
	sigaction(SIGUSR1, &act, NULL);
	print_pid();
	while (1)
	{
		pause();
	}
	return (0);
}
