#ifndef malloc_HEADER
#define malloc_HEADER

/*
* You only need to include stdlib.h to use aci_malloc
* This file is used mainly for debugging purposes
*/

typedef struct aci_malloc_block_s {
    __attribute__((__packed__)) unsigned char  allocated;
    __attribute__((__packed__)) unsigned short size;
    __attribute__((__packed__)) unsigned char  spacer;
} __attribute__((__packed__)) aci_malloc_block_t;

extern int aci_malloc_blocks_n;
extern aci_malloc_block_t * aci_malloc_blocks;

#endif
