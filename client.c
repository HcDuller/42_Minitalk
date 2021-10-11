/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 13:39:49 by hde-camp          #+#    #+#             */
/*   Updated: 2021/10/11 17:35:11 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

int	g_can_go_on = 1;

void	signal_handler(int signo, siginfo_t *info, void *context)
{
	(void)signo;
	(void)info;
	(void)context;
	g_can_go_on = 1;
}

void	set_listeners(void)
{
	struct sigaction	act;

	act.sa_sigaction = &signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}

int	main(int argc, char **argv)
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
		i = 0;
		send_size_t(&size, pid);
		while (i < size)
		{
			send_byte(argv[2][i], pid);
			i++;
		}
	}
	else
		ft_putstr_fd("Ao menos dois argumentos sao necessarios", 1);
	return (0);
}
