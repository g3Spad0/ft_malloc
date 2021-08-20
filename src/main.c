
#include "sys_malloc.h"
#include "ft_malloc.h"

int main() {

//
//	//for (int i = 0; i < 1000; ++i) {
////		char *arr =malloc(10000);
////	//}
////	for (int i = 0; i < 10000; i++) {
////		arr[i] = 65;
////	}
////	show_alloc_mem_ex(LARGE_CHAR, 1, 100, 5);
//
//
//void 	*arr[81];
////free(a);
//	for (int i = 0; i < 81; ++i) {
//		if (i == 70) {
//			free(malloc(50));
//			arr[i] = malloc(2);
//		}
//		else
//		arr[i] = malloc(50);
//	}
//	void *p = malloc(50);
//
//
//
//	free(malloc(1));
//
//	free(p);
//
//	for (int i = 0; i < 80; ++i) {
//		arr[i] = malloc(50);
//	}
//
//
//	for (int i = 0; i < 80; i++) {
//			free(arr[i]);
//		}
//
//	for (int i = 0; i < 90; i++) {
//		malloc(50);
//	}
//
//	free(p + 4343346576);
//
//show_alloc_mem();

#include <stdio.h>
// LARGE

void 	*arr[81];

	for (int i = 0; i < 12; ++i) {

		arr[i] = malloc(1000);
	}

	//free(arr[11]);

	show_alloc_mem();

	free(arr[10]);
	free(arr[11]);
	malloc(120);

//	show_alloc_mem();
	write(1, "-------------\n\n\n\n", strlen("-------------\n\n\n\n"));
//
//
//	for (int i = 24; i < 100; ++i) {
//		free(arr[i]);
//	}

	show_alloc_mem();

return 0;
}
