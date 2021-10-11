/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:14:24 by hde-camp          #+#    #+#             */
/*   Updated: 2021/10/11 17:21:12 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

extern int	g_can_go_on;

void	send_bit(char bit, int pid)
{
	int	sig_success;

	g_can_go_on = 0;
	if (bit)
		sig_success = kill(pid, SIGUSR1);
	else
		sig_success = kill(pid, SIGUSR2);
	if (sig_success == -1)
		ft_putstr_fd("Signal Failed, Review your server PID.\n", 1);
}

void	send_byte(char c, int pid)
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

void	send_size_t(size_t *size, int pid)
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
	}
}
