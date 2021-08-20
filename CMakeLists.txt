cmake_minimum_required(VERSION 3.19)
project(ft_malloc C)

set(CMAKE_C_STANDARD 99)

file(GLOB LIBFT_SRC
        "libft/*.h"
        "libft/*.c"
        )

include_directories(includes)
include_directories(libft)

add_executable(ft_malloc src/main.c includes/sys_malloc.h ${LIBFT_SRC} src/tiny_malloc.c src/utils.c src/tiny_free.c src/large_malloc.c src/large_free.c src/small_malloc.c src/small_free.c src/common.c src/show_alloc_mem.c src/printers.c src/show_alloc_mem_ex.c src/small_malloc_norm.c includes/ft_malloc.h src/check_pointer.c)