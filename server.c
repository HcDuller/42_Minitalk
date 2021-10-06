/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:35:39 by hde-camp          #+#    #+#             */
/*   Updated: 2021/10/06 17:09:21 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<minitalk.h>
#include	<signal.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>

void	reset_handler(size_t *bit_index, int *header_is_loaded, size_t *size, char **str)
{
	ft_putstr_fd("\nconnection reset\n", 1);
	*bit_index = 0;
	*header_is_loaded = 0;
	*size = 0;
	free(*str);
	*str = NULL;
}

void	print_and_reset(size_t *bit_index, int *header_is_loaded, size_t *size, char **str)
{
	ft_putstr_fd(*str, 1);
	reset_handler(bit_index, header_is_loaded, size, str);
}

void	print_iteration(size_t index)
{
	char	*ptr;

	ptr = ft_itoa(index);
	ft_putstr_fd("Msg [",1);
	ft_putstr_fd(ptr,1);
	ft_putstr_fd("] \n",1);
	free(ptr);
}

void	user_sig_handler(int signo, siginfo_t *info, void *context)
{
	static size_t	bit_index = 0;
	static int		header_is_loaded = 0;
	static size_t	size = 0;
	static char		*str = NULL;

	if (!header_is_loaded)
	{
		if (bit_index < 32)
		{
			if (signo == SIGUSR1)
				size = size | (1 << bit_index);
			bit_index++;
			if (bit_index == 32)
			{
				header_is_loaded = 1;
				bit_index = 0;
				str = ft_calloc(size + 1, sizeof(char));
			}
		}
		//print_iteration(bit_index);
	}
	else
	{
		//print_iteration(bit_index + 33);
		if (signo == SIGUSR1)
			str[bit_index / 8] = str[bit_index / 8] | (0b10000000 >> (bit_index % 8));
		bit_index++;
		if (bit_index == size * 8)
			print_and_reset(&bit_index, &header_is_loaded, &size, &str);
	}
	kill(info->si_pid, SIGUSR1);
}

void	eval_size(void)
{
	unsigned long	s;
	int				bit_index;

	s = 0;
	bit_index = 0;
	while (bit_index < 32)
	{
		pause();
	}
}

void	print_pid(int pid)
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
	struct sigaction	act_1;
	struct sigaction	act_2;

	act_1.sa_sigaction = user_sig_handler;
	act_2.sa_sigaction = user_sig_handler;
	print_pid(getpid());
	sigemptyset(&act_1.sa_mask);
	sigemptyset(&act_2.sa_mask);
	act_1.sa_flags = SA_SIGINFO | SA_NODEFER | SA_RESTART;
	act_2.sa_flags = SA_SIGINFO | SA_NODEFER | SA_RESTART;
	sigaction(SIGUSR1, &act_1, NULL);
	sigaction(SIGUSR2, &act_2, NULL);
	while (1)
		pause();
	return (0);
}
