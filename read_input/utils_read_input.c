/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_read_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:14:00 by feazeved          #+#    #+#             */
/*   Updated: 2025/11/18 21:14:15 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_input.h"
#include <sys/ioctl.h>
#include <stdio.h>

static int	stt_ft_parse_cpr(char *buf, int *rows, int *cols)
{
	int	i;
	int	r;
	int	c;

	if (buf[0] != '\033' || buf[1] != '[')
		return (-1);
	i = 2;
	r = 0;
	while (buf[i] >= '0' && buf[i] <= '9')
		r = r * 10 + (buf[i++] - '0');
	if (buf[i++] != ';')
		return (-1);
	c = 0;
	while (buf[i] >= '0' && buf[i] <= '9')
		c = c * 10 + (buf[i++] - '0');
	if (buf[i] != 'R')
		return (-1);
	*rows = r;
	*cols = c;
	return (0);
}

int	get_cursor_absolute_position(int *rows, int *cols)
{
	char	buf[32];
	int		i;
	ssize_t	ret;

	if (write(STDOUT_FILENO, "\033[6n", 4) != 4)
		return (-1);
	i = 0;
	while (i < (int)sizeof(buf) - 1)
	{
		ret = read(STDIN_FILENO, &buf[i], 1);
		if (ret <= 0)
			return (-1);
		if (buf[i] == 'R')
			break;
		i++;
	}
	buf[i + 1] = '\0';
	if (stt_ft_parse_cpr(buf, rows, cols) == -1)
		return (-1);
	(*rows)--;
	(*cols)--;
	return (0);
}

int	get_window_size(int *rows, int *cols)
{
	struct winsize	ws;

	if (g_signal & FT_SIGWINCH)
		g_signal &= ~FT_SIGWINCH;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
		return (perror("msh: ioctl"), -1);
	*cols = ws.ws_col;
	*rows = ws.ws_row;
	return (0);
}

int	rd_handle_sigint(t_line_editor *data)
{
	write(STDOUT_FILENO, "^C\n", 3);
	data->line.ptr[0] = '\0';
	g_signal &= ~FT_SIGINT;
	data->line.length = 0;
	return (0);
}
