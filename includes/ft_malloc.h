/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:44:51 by sjamie            #+#    #+#             */
/*   Updated: 2021/08/08 19:44:54 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem(void);
void			show_alloc_mem_ex(char type, uint32_t zone_number,
					size_t zone_print_size, uint32_t zone_wight_size);

#endif
