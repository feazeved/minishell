/* ************************************************************************** */
/* cursor.c                                           :+:      :+:    :+:   */
/* ************************************************************************** */

#include "read_input.h"

static int	stt_ft_itoa_stack(int64_t number, char *buf)
{
	const int8_t	sign = (number >= 0) - (number < 0);
	char			temp[32];
	int				i;
	int				j;

	number *= sign;
	i = 0;
	if (number < 0)
		number = -number;
	if (number == 0)
		temp[i++] = '0';
	while (number > 0)
	{
		temp[i++] = (number % 10) + '0';
		number /= 10;
	}
	if (sign == -1)
		temp[i++] = '-';
	j = 0;
	while (i > 0)
		buf[j++] = temp[--i];
	buf[j] = '\0';
	return (j);
}

static void	stt_move_up_n(int n)
{
	char	buf[32];
	int		len;

	if (n <= 0)
		return ;
	write(STDOUT_FILENO, "\033[", 2);
	len = stt_ft_itoa_stack(n, buf);
	write(STDOUT_FILENO, buf, len);
	write(STDOUT_FILENO, "A", 1);
}

void	update_cursor_position(t_line_editor *data)
{
	size_t	total_pos;

	total_pos = data->prompt.length + data->cursor_pos;
	data->cursor_y = total_pos / data->screen_cols;
	data->cursor_x = total_pos % data->screen_cols;
}

void	stt_cursor_home(t_line_editor *data)
{
	update_cursor_position(data);
	stt_move_up_n(data->cursor_y);
	write(STDOUT_FILENO, "\r", 1);
}

void	redraw_line(t_line_editor *data)
{
	size_t	total_len;
	int		end_row;
	int		target_row;
	char	buf[32];
	int		len;

	write(STDOUT_FILENO, "\033[0J", 4);
	write(STDOUT_FILENO, data->prompt.ptr, data->prompt.length);
	write(STDOUT_FILENO, data->line.ptr, data->line.length);
	total_len = data->prompt.length + data->line.length;
	end_row = total_len / data->screen_cols;
	update_cursor_position(data);
	target_row = data->cursor_y;
	stt_move_up_n(end_row - target_row);
	write(STDOUT_FILENO, "\r", 1);
	if (data->cursor_x > 0)
	{
		write(STDOUT_FILENO, "\033[", 2);
		len = stt_ft_itoa_stack(data->cursor_x, buf);
		write(STDOUT_FILENO, buf, len);
		write(STDOUT_FILENO, "C", 1);
	}
}
