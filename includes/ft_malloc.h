#ifndef FT_MALLOC_FT_MALLOC_H
#define FT_MALLOC_FT_MALLOC_H

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdint.h>

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem();
void			show_alloc_mem_ex(char type, uint32_t zone_number,
								  size_t zone_print_size, uint32_t zone_wight_size);

void			*alloc_as_tiny(size_t size);
void			memory_write(void *dst, void *src, int size);
void 			add_prompt(char type, void *src);
void 			*default_mmap(size_t size);
void			*free_as_tiny(void *ptr);
void			*alloc_as_large(size_t size);
void			free_as_large(void *ptr);
size_t			get_large_offset();

void			*alloc_as_small(size_t size);
void			free_as_small(void *ptr);

int				can_free(void *src);
uint64_t		print_tiny_return_total();
uint64_t		print_small_return_total();
uint64_t		print_large_return_total();
void			print_zones_tiny(uint32_t zone_number, size_t zone_print_size, uint32_t zone_wight_size);
void			print_zones_small(uint32_t zone_number, size_t zone_print_size, uint32_t zone_wight_size);
void			print_zones_large(uint32_t zone_number, size_t zone_print_size, uint32_t zone_wight_size);
void			print_address(void *ptr);
void			print_uint64_t(uint64_t n);

# define TINY_SIZE_START	0
# define TINY_SIZE_END		50
# define TINE_CHAR			'T'

# define SMALL_SIZE_START	51
# define SMALL_SIZE_END		4096
# define SMALL_CHAR			'S'

# define LARGE_SIZE_START	4097
# define LARGE_SIZE_END		65535
# define LARGE_CHAR			'L'

// 8 - указатель, 2 - сколько свободно
# define TINY_OFFSET		10
# define SMALL_OFFSET		18
# define SMALL_DATA_SIZE	11
# define END_CHAR			2
# define BUSY_CHAR			1
# define FREE_CHAR			0

typedef int bool;
# define true 1
# define false 0

typedef struct			s_tiny_holder
{
	void 				*user_start;
	void 				*user_end;
	void 				*sys_start;
	void 				*sys_end;
}						t_tiny_holder;

typedef struct			s_small_holder
{
	void 				*user_start;
	void 				*user_end;
}						t_small_holder;

typedef struct			s_large_data
{
	struct	s_large_data	*next;
	struct	s_large_data	*prev;
	size_t				mmap_size;
	size_t				real_size;
}						t_large_data;

typedef struct			s_large_holder
{
	t_large_data 		*start;
	t_large_data 		*end;
}						t_large_holder;

typedef struct			s_malloc_data
{
	t_tiny_holder		tiny;
	t_small_holder		small;
	t_large_holder		large;
	int 				pagesize;
}						t_malloc_data;

typedef struct			s_tiny_box
{
	void 				*user;
	void 				*sys;
	int 				offset;
}						t_tiny_box;

typedef struct			s_small_box
{
	void 				*user;
	void				*prev;
	void				*next;
	int 				offset;
	int					user_offset;
}						t_small_box;

extern t_malloc_data	g_malloc_data;


#endif
