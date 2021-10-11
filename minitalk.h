/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:36:03 by hde-camp          #+#    #+#             */
/*   Updated: 2021/10/11 17:45:25 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# define _DEFAULT_SOURCE
# include <unistd.h>
# include <libft.h>
# include <signal.h>

typedef struct s_conn_data {
	size_t	stream_len;
	size_t	stream_len_left;
	int		bit_index;
	int		size_index;
	char	*str;
}	t_conn_data;

void	start_conn_state(t_conn_data *state);
void	msg_size_handler(t_conn_data *conn_state, int signo);
void	reset_conn_state(t_conn_data *conn_state);
void	msg_content_handler(t_conn_data *conn_state, int signo);
void	send_bit(char bit, int pid);
void	send_byte(char c, int pid);
void	send_size_t(size_t *size, int pid);
#endif