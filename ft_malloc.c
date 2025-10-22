/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:32:28 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/19 17:40:47 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	init_ft_malloc(void *memory)
{
	t_block	*first;

	first = (t_block *)memory;
	first->size = MEM_SIZE - sizeof(t_block);
	first->free = 1;
	first->next = NULL;
}

void	merge_blocks(void *memory)
{
	t_block	*current;

	current = (t_block *)memory;
	while (current && current->next)
	{
		if (current->free && current->next->free)
		{
			current->size += current->next->size + sizeof(t_block);
			current->next = current->next->next;
		}
		else
			current = current->next;
	}
}

void	split_block(t_block *fitting_slot, size_t size)
{
	t_block *new;

	new = (void *)((char *)fitting_slot + size + sizeof(t_block));
	new->size = fitting_slot->size - size - sizeof(t_block);
	new->free = 1;
	new->next = fitting_slot->next;
	fitting_slot->size = size;
	fitting_slot->free = 0;
	fitting_slot->next = new;
}

void	*ft_malloc(void *memory, size_t bytes)
{
	t_block	*current;
	
	current = (t_block *)memory;
	if (current->size == 0)
		init_ft_malloc(memory);
	while(current && ((current->size < bytes) || (current->free == 0)))
		current = current->next;
	if (!current)
		return (NULL);
	if (current->size == bytes)
	{
		current->free = 0;
		return ((void *)(current + 1));
	}
	else if (current->size > (bytes + sizeof(t_block)))
	{
		split_block(current, bytes);
		return ((void *)(current + 1));
	}
	else
		return (NULL);
}

void	ft_free(void *memory, void *ptr)
{
	t_block	*block;

	if (!ptr)
		return ;
	if (ptr < memory || (ptr > (void *)((char *)memory + MEM_SIZE)))
		return ;
	block = (t_block *)ptr - 1;
	block->free = 1;
	merge_blocks(memory);
}

int	main()
{
	char	arena[MEM_SIZE] = {0};
	char	*str;

	str = ft_malloc(arena, 5 * sizeof(char));
	if (!str)
		return (1);
	str = "arara";
	printf("%s\n", str);
	return (0);
}
