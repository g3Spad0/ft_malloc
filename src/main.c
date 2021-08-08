
#include "ft_malloc.h"

int main() {


	for (int i = 0; i < 1000; ++i) {
		malloc(1000);
	}
	show_alloc_mem();
    return 0;
}



