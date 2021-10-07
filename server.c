/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:11:02 by hde-camp          #+#    #+#             */
/*   Updated: 2021/10/06 21:07:18 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<minitalk.h>
#include	<signal.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>

typedef struct s_conn_data {
	size_t	stream_len;
	size_t	stream_len_left;
	int		bit_index;
	int		size_index;
	char	*str;
} t_conn_data;

void	print_size(size_t size)
{
	char	*ptr;

	ptr = ft_itoa(size);
	ft_putstr_fd("size received[", 1);
	ft_putstr_fd(ptr, 1);
	ft_putstr_fd("]\n", 1);
	free(ptr);
}

void	start_conn_state(t_conn_data *state)
{
	state->stream_len = 0;
	state->stream_len_left = 0;
	state->bit_index = 7;
	state->size_index = 31;
	state->str = NULL;
}

void	sig_handler(int signo, siginfo_t *info, void *context)
{
//connecxao aberta?
//ja recebeu stream_len?
//tamanho da stream em bytes (stream_len)
//bit a ser recebido
	static t_conn_data conn_state = {0, 0, 7, 31, NULL};
	static char		*str;
	size_t			byte_index;

	//start_conn_state(&conn_state);
	if (conn_state.size_index >= 0)
	{
		if (signo == SIGUSR1)
			conn_state.stream_len |= (0b10000000000000000000000000000000 >> conn_state.size_index);
		conn_state.size_index--;
		if (conn_state.size_index < 0)
		{
			print_size(conn_state.stream_len);
			str = ft_calloc(conn_state.stream_len + 1, sizeof(char));
			conn_state.stream_len_left = conn_state.stream_len;
		}	
	}
	else
	{
		byte_index = conn_state.stream_len - conn_state.stream_len_left;
		if (signo == SIGUSR1)
			conn_state.str[byte_index] |= 0b10000000 >> conn_state.bit_index;
		conn_state.bit_index--;
		if (conn_state.bit_index == -1)
		{
			conn_state.bit_index = 7;
			conn_state.stream_len_left--;
		}
		if (conn_state.stream_len_left == 0)
		{
			ft_putstr_fd(conn_state.str, 1);
			ft_putstr_fd("\n", 1);
			free(conn_state.str);
			str = NULL;
			conn_state.stream_len = 0;
			conn_state.stream_len_left = 0;
			conn_state.bit_index = 7;
			conn_state.size_index = 31;
		}
	}
	kill(info->si_pid, SIGUSR1);
}

void	set_listeners()
{
	struct sigaction	act;

	sigaction(SIGUSR1,NULL, &act);
	act.sa_flags = 0 | SA_SIGINFO | SA_NODEFER;
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	ft_putstr_fd("Listeners were set\n", 1);
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
	print_pid(getpid());
	set_listeners();
	while (1)
		pause();
	return (0);
}