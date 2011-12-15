#ifndef aci_malloc_HEADER
#define aci_malloc_HEADER

#include "stdlib.h"
// gives us ACI_HEAP_BEGIN and ACI_HEAP_SIZE from arch
#include "../config.h"
#include "../aci.h"

#include "malloc.h"

int aci_malloc_blocks_n = 0;

aci_malloc_block_t * aci_malloc_blocks = (aci_malloc_block_t *) ACI_HEAP_BEGIN;

void * aci_malloc_align (unsigned int size, unsigned int align)
{
    char buf[64];
    aci_vga_write("HI\n");
    aci_sprintf(buf, "aci_malloc_align %x %x %x %x\n", 
                aci_malloc_blocks_n, aci_malloc_blocks, 0xdeadbeef, ACI_HEAP_BEGIN);
    aci_vga_write(buf);


    void * ret;
    aci_malloc_block_t * block;
    int block_i;
    word_t cmp;
    unsigned int alignment_needed;

    block = aci_malloc_blocks;

    // no blocks
    if (aci_malloc_blocks_n == 0) {
        aci_vga_write("no blocks\n");
        block->allocated = 1;
        block->size = size;
        ret = (void *) block + sizeof(aci_malloc_block_t);
        aci_sprintf(buf, "%x %x %x\n", sizeof(aci_malloc_block_t), ret, block);
        aci_vga_write(buf);
        aci_malloc_blocks_n++;

        // align block
        alignment_needed = (unsigned int) block + sizeof(aci_malloc_block_t);
        alignment_needed %= align;
        if (alignment_needed) {
            block->size += align;
            ret += align - alignment_needed;
        }
        return ret;
    }
    // blocks exist
    else {
        aci_vga_write("blocks exist\n");
        // looks for a suitable free block
        for (block_i = 0; block_i < aci_malloc_blocks_n; block_i++) {
            if (block->allocated == 1) {
                block = (void *) block + sizeof(aci_malloc_block_t) + block->size;
                continue;
            }
            // is this block, accounting for alignment, large enough to hold
            // this memory ?
            if (block->size <= size + alignment_needed) {
                block->allocated = 1;
                ret = (void *) block + sizeof(aci_malloc_block_t);

                alignment_needed = (unsigned int) block + sizeof(aci_malloc_block_t);
                alignment_needed %= align;
                if (alignment_needed) {
                    block->size += align;
                    ret += align - alignment_needed;
                }
                return ret;
            }
            block = (void *) block + sizeof(aci_malloc_block_t) + block->size;
        }
    }
    // do we have space for another block
    if ((word_t) block + size < ACI_HEAP_BEGIN + ACI_HEAP_SIZE) {
        aci_vga_write("space for another block\n");
        block->allocated = 1;
        block->size = size;
        ret = (void *) block + sizeof(aci_malloc_block_t);

        aci_vga_write(buf);

        alignment_needed = (unsigned int) block + sizeof(aci_malloc_block_t);
        alignment_needed %= align;
        if (alignment_needed) {
            block->size += align;
            ret += align - alignment_needed;
        }
        aci_sprintf(buf, "%x %x %x\n", ret, align, alignment_needed);
        aci_vga_write(buf);
        aci_malloc_blocks_n++;
        return ret;
    }

    aci_vga_write("returning null\n");
    return NULL;
}

void * aci_malloc (unsigned int size)
{
    return aci_malloc_align(size, 4);
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
