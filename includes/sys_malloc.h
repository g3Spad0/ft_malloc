/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_malloc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:45:00 by sjamie            #+#    #+#             */
/*   Updated: 2021/08/08 19:45:06 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYS_MALLOC_H
# define SYS_MALLOC_H

# include <sys/mman.h>
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>

# define TINY_SIZE_START	0
# define TINY_SIZE_END		50
# define TINE_CHAR			'T'

# define SMALL_SIZE_START	51
# define SMALL_SIZE_END		4096
# define SMALL_CHAR			'S'

# define LARGE_SIZE_START	4097
# define LARGE_SIZE_END		65535
# define LARGE_CHAR			'L'

# define FREE_DONE_CHAR		'D'

// 8 - указатель, 2 - сколько свободно
# define TINY_OFFSET		10
# define SMALL_OFFSET		18
# define S_D_S				11
# define END_CHAR			2
# define BUSY_CHAR			1
# define FREE_CHAR			0
# define TRUE 1
# define FALSE 0

typedef int	t_bool;

typedef struct s_tiny_holder
{
	void					*user_start;
	void					*user_end;
	void					*sys_start;
	void					*sys_end;
}							t_tiny_holder;

typedef struct s_small_holder
{
	void					*user_start;
	void					*user_end;
}							t_small_holder;

typedef struct s_large_data
{
	struct s_large_data		*next;
	struct s_large_data		*prev;
	size_t					mmap_size;
	size_t					real_size;
}							t_large_data;

typedef struct s_large_holder
{
	t_large_data			*start;
	t_large_data			*end;
}							t_large_holder;

typedef struct s_malloc_data
{
	t_tiny_holder			tiny;
	t_small_holder			small;
	t_large_holder			large;
	int						pagesize;
}							t_malloc_data;

typedef struct s_tiny_box
{
	void					*user;
	void					*sys;
	int						offset;
}							t_tiny_box;

typedef struct s_small_box
{
	void					*user;
	void					*prev;
	void					*next;
	int						offset;
	int						user_offset;
}							t_small_box;

typedef struct s_small_norm
{
	void					*user_pointer;
	void					*curr_pointer;
	int16_t					curr_size;
	void					*prev;
	void					*old_user_pointer;
}							t_small_norm;

typedef struct s_pair
{
	void					*sys_pointer;
	void					*user_pointer;
}							t_pair;

extern	t_malloc_data
			g_malloc_data;

t_bool						is_in_start(t_small_box *box,
								size_t size,
								void *user_pointer,
								void *curr_pointer);

void						set_norm(t_small_box *box,
								void *user_pointer,
								void *curr_pointer,
								void *tmp);

t_bool						tiny_malloc_norm(t_tiny_box *box,
								void *sys_pointer,
								void *user_pointer,
								int v);

void						*alloc_as_tiny(size_t size);
void						memory_write(void *dst, void *src, int size);
void						add_prompt(char type, void *src);
void						*default_mmap(size_t size);
void						free_as_tiny(void *ptr);
void						*alloc_as_large(size_t size);
void						free_as_large(void *ptr);
size_t						get_large_offset(void);
void						*alloc_as_small(size_t size);
void						free_as_small(void *ptr);
int							can_free(void *src);
uint64_t					print_tiny_return_total(void);
uint64_t					print_small_return_total(void);
uint64_t					print_large_return_total(void);
void						print_zones_tiny(uint32_t zone_number,
								size_t zone_print_size,
								uint32_t zone_wight_size);
void						print_zones_small(uint32_t zone_number,
								size_t zone_print_size,
								uint32_t zone_wight_size);
void						print_zones_large(uint32_t zone_number,
								size_t zone_print_size,
								uint32_t zone_wight_size);
void						print_address(void *ptr);
void						print_uint64_t(uint64_t n);
void						print_char_as_hex(char c);
t_bool						can_free_pointer(void *ptr);
void						ft_bzero(void *s, size_t n);
void						ft_putchar(char c);
void						ft_putstr(char const *s);
void						start_free(void *ptr, t_bool check_valid);
long long					to_ll(size_t size);

#endif
