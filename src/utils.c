#include "ft_malloc.h"

void			memory_write(void *dst, void *src, int size)
{
	int		i;
	char	*c_dst;
	char 	*c_src;

	c_dst = (char *)dst;
	c_src = (char *)src;
	i = 0;
	while (i < size)
	{
		c_dst[i] = c_src[i];
		i++;
	}
}

void 		add_prompt(char type, void *src)
{
	char 	*c_src;

	c_src = (char *)src;
	c_src[0] = type;
}

int			can_free(void *src)
{
	char	*c_src;
	char	c;

	c_src = (char *)src;
	c = c_src[0];
	return (c == TINE_CHAR || c == SMALL_CHAR || c == LARGE_CHAR);
}

void 		*default_mmap(size_t size)
{
	return mmap(0, size, PROT_READ | PROT_WRITE, \
			MAP_ANON | MAP_PRIVATE, -1, 0);
}
