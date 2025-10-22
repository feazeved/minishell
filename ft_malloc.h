/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:33:41 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/19 17:40:15 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdio.h>
# include <stddef.h>

# define MEM_SIZE 20000

typedef struct s_block
{
	size_t			size;
	int				free;
	struct s_block	*next;	
}	t_block;

void	*ft_malloc(void *memory, size_t bytes);
void	ft_free(void *memory, void *ptr);
void	init_ft_malloc(void *memory);
void	split_block(t_block *fitting_slot, size_t size);
void	merge_blocks();

#endif
