/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 10:44:17 by adeimlin          #+#    #+#             */
/*   Updated: 2025/11/11 15:47:22 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include "minishell.h"

#define PROMPT "lfsh:"

int	g_status;

void	non_interactive_shell(t_shell *shell, t_token *tokens)
{
	
}

void	print_prompt(void)
{
	write(1, PROMPT, ft_strlen(PROMPT));
}

void	interactive_shell(t_shell *shell)
{
	char	line[4096];

	setup_signals();
	setup_terminal();
	while (1)
	{
		print_prompt();
		if (read_intput(shell->hist, &line, sizeof(line)) == -1)
			break ;
		if (!line[0])
			continue ;
		/* add to history*/
		if (tokenize(shell) == -1)
			continue ;
		execute(shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argc;
	ft_memset(&shell, 0, sizeof(shell));
	env_init(&shell.env, envp);
	//shlvl();
	if (isatty(STDIN_FILENO))
		interactive_shell(&shell);
	else
		non_interactive_shell(&shell, NULL);
	exit(0);
}
