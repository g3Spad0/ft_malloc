#include "ft_malloc.h"
#include <stdio.h>

void			print_address(void *ptr)
{
	char arr[100];

	sprintf(arr, "%p", ptr);
	ft_putstr(arr);
}

void			print_char_as_hex(char c)
{

}

void			print_uint64_t(uint64_t n)
{
	uint64_t	num;
	uint64_t	ten;
	uint64_t	tmp;

	if (n == 0)
		return (ft_putchar('0'));
	num = n;
	ten = 1;
	while (num / ten)
		ten *= 10;
	ten /= 10;
	while (ten)
	{
		tmp = num / ten;
		ft_putchar(tmp + 48);
		num -= ten * tmp;
		ten /= 10;
	}
}
