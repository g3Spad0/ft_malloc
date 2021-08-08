#include "ft_malloc.h"

static	uint64_t	items_tiny_return_total(void *sys_pointer, void *user_pointer)
{
	char 		*arr;
	int 		i;
	int 		j;
	uint64_t	total;

	i = TINY_OFFSET;
	arr = (char*)sys_pointer;
	total = 0;
	while (i < g_malloc_data.pagesize)
	{
		if (arr[i] == BUSY_CHAR)
		{
			j = 0;
			while (arr[j + i] == BUSY_CHAR)
				++j;
			if (arr[j + i] == END_CHAR)
				j += 1;
			total += j;
			print_address(user_pointer + i + 1);
			ft_putstr(" - ");
			print_address(user_pointer + i + j);
			ft_putstr(" : ");
			print_uint64_t((uint64_t) (j - 1));
			ft_putstr(" bytes\n");
			i = j + i - 1;
		}
		++i;
	}
	return (total);
}

uint64_t			print_tiny_return_total()
{
	uintptr_t	sys_pointer_offset;
	void 		*sys_pointer;
	uintptr_t	user_pointer_offset;
	void 		*user_pointer;
	uint64_t	total;

	sys_pointer_offset = (uintptr_t) g_malloc_data.tiny.sys_start;
	user_pointer_offset = (uintptr_t) g_malloc_data.tiny.user_start;
	total = 0;
	while (user_pointer_offset != 0)
	{
		sys_pointer = (NULL) + sys_pointer_offset;
		user_pointer = (NULL) + user_pointer_offset;
		ft_putstr("TINY : ");
		print_address(user_pointer);
		ft_putstr("\n");
		total += items_tiny_return_total(sys_pointer, user_pointer);
		if (sys_pointer == g_malloc_data.tiny.sys_end)
			break ;
		memory_write(&sys_pointer_offset, sys_pointer, 8);
		memory_write(&user_pointer_offset, user_pointer, 8);
	}
	return (total);
}

static	uint64_t	items_small_return_total(void *user_pointer)
{
	void	*curr_pointer;
	void	*next;
	int16_t	curr_size;
	uint64_t	total;

	total = 0;
	memory_write(&curr_pointer, user_pointer + 8 + 2, 8);
	while (curr_pointer != NULL)
	{
		memory_write(&next, curr_pointer, 8);
		memory_write(&curr_size, curr_pointer + 8, 2);
		print_address(curr_pointer + SMALL_DATA_SIZE);
		ft_putstr(" - ");
		print_address(curr_pointer + curr_size - SMALL_DATA_SIZE);
		ft_putstr(" : ");
		print_uint64_t((uint64_t) (curr_size - SMALL_DATA_SIZE));
		ft_putstr(" bytes\n");
		total += curr_size - SMALL_DATA_SIZE;
		curr_pointer = next;
	}
	return (total);
}

uint64_t			print_small_return_total()
{
	uintptr_t	user_pointer_offset;
	void 		*user_pointer;
	uint64_t	total;

	user_pointer_offset = (uintptr_t) g_malloc_data.small.user_start;
	total = 0;
	while (user_pointer_offset != 0)
	{
		user_pointer = (NULL) + user_pointer_offset;
		ft_putstr("SMALL : ");
		print_address(user_pointer);
		ft_putstr("\n");
		total += items_small_return_total(user_pointer);
		if (user_pointer == g_malloc_data.small.user_end)
			break ;
		memory_write(&user_pointer_offset, user_pointer, 8);
	}
	return (total);
}

uint64_t			print_large_return_total()
{
	t_large_data	*data;
	uint64_t		total;

	data = g_malloc_data.large.start;
	total = 0;
	while (data != NULL)
	{
		ft_putstr("LARGE : ");
		print_address(data);
		ft_putstr("\n");
		print_address(data);
		ft_putstr(" - ");
		print_address(data + data->real_size);
		ft_putstr(" : ");
		print_uint64_t((uint64_t) data->real_size);
		ft_putstr(" bytes\n");
		total += data->real_size;
		data = data->next;
	}
	return (total);
}