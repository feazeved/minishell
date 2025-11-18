#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

typedef struct	s_line
{
	char	*buffer;
	size_t	len;
	size_t	max;
}	t_line;

typedef struct	s_line_editor
{
	struct termios	old_terminal;
	t_line			line;
	int				screen_rows;
	int				screen_cols;
	int				cursor_x;
	int				cursor_y;
}	t_line_editor;

// return 0 on success and -1 on error
int	enable_raw_mode(t_line_editor *data)
{
	struct termios	raw_mode;

	if (tcgetattr(STDIN_FILENO, &data->old_terminal) == -1)
		return (perror("tcsetattr"), -1);
	raw_mode = data->old_terminal;
	raw_mode.c_lflag &= ~(ICANON | ECHO);
	raw_mode.c_cc[VMIN] = 1;
	raw_mode.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_mode) == -1)
		return (perror("tcsetattr"), -1);
}

int	disable_raw_mode(t_line_editor *data)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &data->old_terminal) == -1)
		return (perror("tcsetattr"), -1);
}

char	read_key()
{
	ssize_t	ret;
	char	c;

	while ()

}

int	process_key(t_line_editor *data)
{
	const char	c = read_key();

	if (c == -1)
		return (-1);
	else if ()
	if (c == 27)
		handle_arrows();
	else if (c == '\n')
		finaline_line();
	else if ()

}

int	get_window_size(int *rows, int *cols)
{
	struct winsize	ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
		return (perror("ioctl"), -1);
	*cols = ws.ws_col;
	*rows = ws.ws_row;
	return (0);
}

int	init_line_editor(t_line_editor *data, char **buffer, size_t buffer_size)
{
	data->line.buffer = buffer;
	data->line.max = buffer_size;
	if (get_window_size(data->screen_rows, data->screen_cols) == -1)
		return (-1);
	return (0);
}

int	read_input(char	**buffer, size_t buffer_size)
{
	t_line_editor	data;

	if (init_line_editor(&data, buffer, buffer_size) == -1)
		return (-1);
	if (enable_raw_mode(&data) == -1)
		return (-1);
	while (1)
	{
		process_key(&data);
	}
	if (disable_raw_mode(&data) == -1)
		return (-1);
	return (data.line.len);
}



int	main()
{
	read_input();
}