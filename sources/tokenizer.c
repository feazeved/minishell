/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:03:36 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/22 16:05:22 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize(t_shell *shell)
{
	int	i;
	int	tok_i;

	i = 0;
	tok_i = 0;
	while (shell->input[i])
	{
		if (tok_i >= FT_TOKEN_MAX)
			return (ft_write(2, "minishell: too many tokens\n", 27), -1);
		
	}
}
