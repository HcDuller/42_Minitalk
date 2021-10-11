/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:09:10 by hde-camp          #+#    #+#             */
/*   Updated: 2021/10/11 17:09:27 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	start_conn_state(t_conn_data *state)
{
	state->stream_len = 0;
	state->stream_len_left = 0;
	state->bit_index = 7;
	state->size_index = 31;
	state->str = NULL;
}

void	msg_size_handler(t_conn_data *conn_state, int signo)
{
	size_t	mask;

	mask = 0b10000000000000000000000000000000;
	if (signo == SIGUSR1)
		conn_state->stream_len |= (mask >> conn_state->size_index);
	conn_state->size_index--;
	if (conn_state->size_index < 0)
	{
		conn_state->str = ft_calloc(conn_state->stream_len + 1, sizeof(char));
		conn_state->stream_len_left = conn_state->stream_len;
	}
}

void	reset_conn_state(t_conn_data *conn_state)
{
	free(conn_state->str);
	conn_state->stream_len = 0;
	conn_state->stream_len_left = 0;
	conn_state->bit_index = 7;
	conn_state->size_index = 31;
}

void	msg_content_handler(t_conn_data *conn_state, int signo)
{
	size_t	byte_index;
	int		mask;

	mask = 0b10000000;
	byte_index = conn_state->stream_len - conn_state->stream_len_left;
	if (signo == SIGUSR1)
		(conn_state->str)[byte_index] |= mask >> conn_state->bit_index;
	conn_state->bit_index--;
	if (conn_state->bit_index == -1)
	{
		conn_state->bit_index = 7;
		conn_state->stream_len_left--;
	}
	if (conn_state->stream_len_left == 0)
	{
		ft_putstr_fd(conn_state->str, 1);
		ft_putstr_fd("\n", 1);
		reset_conn_state(conn_state);
	}
}
