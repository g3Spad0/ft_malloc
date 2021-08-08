#include "ft_malloc.h"

static	void	print_zone(size_t zone_print_size, uint32_t zone_wight_size,
							 char *zone, size_t real_zone_size)
{
	size_t	i;

	i = 0;
	while (i < zone_print_size)
	{

		if (i != 0 && i % zone_wight_size == 0)
			ft_putstr("\n");
		else
			ft_putstr(" ");
		++i;
	}
	ft_putstr("\n");
}

void			print_zones_tiny(uint32_t zone_number, size_t zone_print_size, uint32_t zone_wight_size)
{

}

void			print_zones_small(uint32_t zone_number, size_t zone_print_size, uint32_t zone_wight_size)
{

}

void			print_zones_large(uint32_t zone_number, size_t zone_print_size, uint32_t zone_wight_size)
{
	uint32_t	curr_number;
	t_large_data	*data;

	curr_number = 1;
	data = g_malloc_data.large.start;
	while (data != NULL)
	{
		if (curr_number == zone_number)
		{
			print_zone(zone_print_size, zone_wight_size,
					   (char*) data, data->mmap_size);
			return ;
		}
		data = data->next;
	}
	ft_putstr("zone not found\n");
}
