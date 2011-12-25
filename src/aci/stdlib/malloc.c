#ifndef aci_malloc_HEADER
#define aci_malloc_HEADER

#include "stdlib.h"
// gives us ACI_HEAP_BEGIN and ACI_HEAP_SIZE from arch
#include "../config.h"
#include "../aci.h"

#include "malloc.h"

int aci_malloc_blocks_n = 0;

aci_malloc_block_t * aci_malloc_blocks = (aci_malloc_block_t *) ACI_HEAP_BEGIN;

void * aci_malloc (unsigned int size)
{
    void * ret;
    aci_malloc_block_t * block;
    int block_i;
    word_t cmp;

    block = aci_malloc_blocks;

    // no blocks
    if (aci_malloc_blocks_n == 0) {
        block->allocated = 1;
        block->size = size;
        ret  = block;
        ret += sizeof(aci_malloc_block_t);
        aci_malloc_blocks_n++;
        return ret;
    }

    // blocks exist
    else {
        // looks for a suitable free block
        for (block_i = 0; block_i < aci_malloc_blocks_n; block_i++) {
            if (block->allocated == 1) {
                block = (void *) block + sizeof(aci_malloc_block_t) + block->size;
                continue;
            }
            if (block->size >= size) {
                block->allocated = 1;
                ret  = (void *) block;
                ret += sizeof(aci_malloc_block_t);
                return ret;
            }
            block = (void *) block + sizeof(aci_malloc_block_t) + block->size;
        }
    }
    // do we have space for another block
    if ((word_t) block + size < ACI_HEAP_BEGIN + ACI_HEAP_SIZE) {
        block->allocated = 1;
        block->size = size;
        ret  = (void *) block;
        ret += sizeof(aci_malloc_block_t);
        aci_malloc_blocks_n++;
        return ret;
    }

    return NULL;
}

// ok i admit this is pretty bad
void * aci_realloc (void * address, unsigned int size)
{
    aci_malloc_block_t * block;
    void * new_mem;

    block = address - sizeof(aci_malloc_block_t);

    if (address == NULL)
        return aci_malloc(size);

    new_mem = aci_malloc(size);
    if (new_mem == NULL)
        return NULL;

    aci_memcpy(new_mem, address, (block->size < size ? block->size : size));
    aci_free(address);

    return new_mem;
}

int aci_free (void * address)
{
    
    char buf[32];
    aci_malloc_block_t * block;

    block = address - sizeof(aci_malloc_block_t);
    if (block->allocated != 1) {
        aci_vga_write("aci_free invalid block error\n");
        aci_sprintf(buf, "%x %x\n", address, block);
        aci_vga_write(buf);
        return -1;
    }

    block->allocated = 0;
    return 0;
}

#endif
