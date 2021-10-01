/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 13:39:49 by hde-camp          #+#    #+#             */
/*   Updated: 2021/09/29 20:24:13 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

int	keep_going = 0;

void	one_handler(int signo, siginfo_t *info, void *context)
{
	keep_going = 1;
}

int	ignore_signal(int signum)
{
	struct	sigaction	act;

	if (sigaction(signum, NULL, &act) == -1)
		return (-1);
	else if (act.sa_handler == SIG_DFL)
	{
		act.sa_flags = SA_SIGINFO;
		act.sa_sigaction = one_handler;
		if (sigaction(SIGINT, &act, NULL) == -1)
			return (-1);
	}
	return (0);
}

int	main(int argc,char **argv)
{
	int					pid;
	int					pseudo_morse;
	char				*str;
	struct	sigaction	act,act2;

	sigemptyset(&act.sa_mask);
	sigemptyset(&act2.sa_mask);
	sigaction(SIGUSR1, NULL, &act);
	sigaction(SIGUSR2, NULL, &act2);
	act.sa_flags = SA_SIGINFO;
	act2.sa_flags = SA_SIGINFO;
	act.sa_sigaction = one_handler;
	act2.sa_sigaction = one_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act2, NULL);
	
	if (argc > 1)
	{
		ft_putstr_fd(argv[1], 1);
		ft_putstr_fd("\n", 1);
		pid = ft_atoi(argv[1]);
		str = (char *) argv[2];
		while (*str != 0){
			pseudo_morse = (int) *str;
			while (pseudo_morse > 0)
			{
				if (keep_going == 1)
				{
					pseudo_morse --;
					keep_going = 0;
				}
				if (keep_going == 0 && pseudo_morse > 0)
				{
					keep_going = -1;
					kill(pid, SIGUSR1);
				}
			}
			kill(pid, SIGUSR2);
			str++;
		}
		return (0);
	}
	return (-1);
}
