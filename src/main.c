
#include "sys_malloc.h"
#include "ft_malloc.h"

int main() {


	//for (int i = 0; i < 1000; ++i) {
		char *arr =malloc(10000);
	//}
	for (int i = 0; i < 10000; i++) {
		arr[i] = 65;
	}
	show_alloc_mem_ex(LARGE_CHAR, 1, 100, 5);
}



