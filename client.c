/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 13:39:49 by hde-camp          #+#    #+#             */
/*   Updated: 2021/10/06 19:50:33 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

int	g_can_go_on = 1;

void	signal_handler(int signo, siginfo_t *info, void *context)
{
	g_can_go_on = 1;
}

void	send_bit(char bit, int pid)
{
	int	sig_success;

	g_can_go_on = 0;
	if (bit)
		sig_success = kill(pid, SIGUSR1);
	else
		sig_success = kill(pid, SIGUSR2);
	if (sig_success == -1)
		ft_putstr_fd("Signal Failed\n", 1);
}

void	send_byte(char c,int pid)
{
	int	i;

	i = 7;
	while (i > -1)
	{
		if (g_can_go_on)
		{
			send_bit((0b10000000 >> i) & c, pid);
			i--;
		}
	}
}

void	send_size_t(size_t *size,int pid)
{
	int		b_shifter;
	size_t	mask;

	b_shifter = 31;
	mask = 0b10000000000000000000000000000000;
	while (b_shifter >= 0)
	{
		if (g_can_go_on)
		{
			if ((mask >> b_shifter) & *size)
				send_bit(1, pid);
			else
				send_bit(0, pid);
			b_shifter--;
		}
		if (!usleep(1000000))
		{
			ft_putstr_fd("Empaquei Aqui\n", 1);
			g_can_go_on = 1;
		}
	}
}

void	print_size(size_t size)
{
	char	*ptr;

	ptr = ft_itoa(size);
	ft_putstr_fd("Size: ", 1);
	ft_putstr_fd(ptr, 1);
	ft_putstr_fd("\n", 1);
	free(ptr);
}

void	set_listeners()
{
	struct	sigaction	act;

	act.sa_sigaction = &signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}

int	main(int argc,char **argv)
{
	int		pid;
	size_t	size;
	size_t	size_in_bits;
	size_t	i;

	set_listeners();
	if (argc > 2)
	{
		pid = ft_atoi(argv[1]);
		size = ft_strlen(argv[2]);
		size_in_bits = 8 * size;
		print_size(size);
		i = 0;
		send_size_t(&size, pid);
		while (i < size)
		{
			send_byte(argv[2][i], pid);
			i++;
		}
		ft_putstr_fd("Finished \n", 1);
	}
	else
		ft_putstr_fd("Ao menos dois argumentos sao necessarios", 1);
	return (0);
}