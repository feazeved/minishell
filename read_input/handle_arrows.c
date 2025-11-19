/* ************************************************************************** */
/* handle_arrows.c                                    :+:      :+:    :+:   */
/* ************************************************************************** */

#include <unistd.h>
#include "read_input.h"

void	stt_cursor_home(t_line_editor *data);

int	move_cursor_left(t_line_editor *data)
{
	if (data->cursor_pos == 0)
		return (0);
	
	if (data->cursor_x == 0)
	{
		write(STDOUT_FILENO, "\033[A", 3);
		write(STDOUT_FILENO, "\033[999C", 6);
	}
	else
	{
		write(STDOUT_FILENO, "\033[D", 3);
	}
	data->cursor_pos--;
	update_cursor_position(data);
	return (0);
}

int	move_cursor_right(t_line_editor *data)
{
	if (data->cursor_pos >= data->line.length)
		return (0);
	if (data->cursor_x >= data->screen_cols - 1)
	{
		write(STDOUT_FILENO, "\033[B", 3);
		write(STDOUT_FILENO, "\r", 1);
	}
	else
	{
		write(STDOUT_FILENO, "\033[C", 3);
	}
	data->cursor_pos++;
	update_cursor_position(data);
	return (0);
}

int	stt_history_prev(t_line_editor *data)
{
	t_hst	*hist;
	char	temp[FT_LINE_MAX];
	size_t	len;

	hist = data->history;
	if (hist->count == 0)
		return (0);
	if (data->hist_current == hist->count)
		data->hist_current = hist->count - 1;
	else if (data->hist_current > 0)
		data->hist_current--;
	else
		return (0);
	len = hst_read(data->hist_current, temp, hist);
	if (len == SIZE_MAX)
		return (0);
	stt_cursor_home(data);
	ft_memcpy(data->line.ptr, temp, len);
	data->line.length = len;
	data->line.ptr[len] = '\0';
	data->cursor_pos = len;
	redraw_line(data);
	return (0);
}

int	stt_history_next(t_line_editor *data)
{
	t_hst	*hist;
	char	temp[FT_LINE_MAX];
	size_t	len;

	hist = data->history;
	if (hist->count == 0 || data->hist_current >= hist->count)
		return (0);
	data->hist_current++;
	stt_cursor_home(data);
	if (data->hist_current >= hist->count)
	{
		data->line.length = 0;
		data->line.ptr[0] = '\0';
		data->cursor_pos = 0;
		redraw_line(data);
		return (0);
	}
	len = hst_read(data->hist_current, temp, hist);
	if (len == SIZE_MAX)
		return (0);
	ft_memcpy(data->line.ptr, temp, len);
	data->line.length = len;
	data->line.ptr[len] = '\0';
	data->cursor_pos = len;
	redraw_line(data);
	return (0);
}

int	handle_arrows(t_line_editor *data)
{
	char	seq[2];

	if (read_key(&seq[0]) != 1)
		return (0);
	if (seq[0] != '[')
		return (0);
	if (read_key(&seq[1]) != 1)
		return (0);
	if (seq[1] == 'A')
		return (stt_history_prev(data));
	else if (seq[1] == 'B')
		return (stt_history_next(data));
	else if (seq[1] == 'C')
		return (move_cursor_right(data));
	else if (seq[1] == 'D')
		return (move_cursor_left(data));
	return (0);
}