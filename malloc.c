#include<stdio.h>
#include<stddef.h>

char memory[20000];

typedef struct s_block
{
	size_t size;
	int free;
	struct block *next; 
}	t_block;

struct block *freeList=(void*)memory;

void	initialize();
void	split(struct block *fitting_slot,size_t size);
void	*MyMalloc(size_t noOfBytes);
void	merge();
void	MyFree(void* ptr);


void	initialize()
{
	free_list->size = 20000-sizeof(t_block);
	free_list->free = 1;
	free->list->next = NULL;
}

void	split(t_block *fitting_slot, size_t size)
{
	t_block	*new;

	new = (void *)((void *)fitting_slot + size + sizeof(t_block));
	new->size = (fitting_slot->size) - size - sizeof(t_block);
	new->free = 1;
	new->next = fitting_slot->next;
	fitting_slot->size = size;
	fitting_slot->free = 0;
	fitting_slot->next = new;


}

int	main()
{
	int		*p;
	char	*q;
	int		*r;

	p = mymalloc(100 * sizeof(int));
	q = mymalloc(250 * sizeof(char));
	r = mymalloc(1000 * sizeof(int));




}
