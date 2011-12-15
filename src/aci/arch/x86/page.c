#include "page.h"
#include "../../stdlib/stdlib.h"

unsigned int * ax86_frames;
unsigned int ax86_frames_n;

void ax86_frame_set (unsigned int address)
{
    address /= ACI_PAGE_SIZE;
    ax86_frames[address / 32] |= 1 << (address % 32);
}

void ax86_frame_clear (unsigned int address)
{
    address /= ACI_PAGE_SIZE;
    ax86_frames[address / 32] &= ~(1 << (address % 32));
}

int ax86_frame_get (unsigned int address)
{
    address /= ACI_PAGE_SIZE;
    return (ax86_frames[address / 32] & (1 << (address % 32))) >> (address % 32);
}

// does not return an address. returns the frame index.
// returns -1 if no frames are free
int ax86_frame_free ()
{
    unsigned int i;
    for (i = 0; i < ax86_frames_n; i += 32) {
        if (ax86_frames[i] == 0xffffffff)
            continue;
        while (1)
            if (ax86_frame_get(i * ACI_PAGE_SIZE))
                return i;
    return -1;
}


// returns
//  0 on success
//  1 if page already has a frame
// -1 if no free frames are available
int ax86_frame_alloc (ax86_page_t * page, int user, int rw)
{
    unsigned int free_frame;

    if (page->frame != 0)
        return 1;
    
    free_frame = ax86_frame_free();
    if (free_frame == (unsigned int) -1)
        return -1;

    ax86_frame_set(free_frame * ACI_PAGE_SIZE);
    page->present = 1;
    page->rw      = write;
    page->user    = user;
    page->frame   = free_frame;

    return 0;
}

// returns
//  0 on success
// -1 if page was not set
int ax86_frame_free (ax86_page_t * page)
{
    unsigned int frame;
    
    if (page->present == 0)
        return -1;

    ax86_frame_clear(page->frame);
    page->present = 0;
    page->frame   = 0;

    return 0;
}

void ax86_page_init ()
{
    ax86_frames_n = ACI_MEM_SIZE / ACI_PAGE_SIZE;
    ax86_frames   = aci_kmalloc(ax86_frames_n / 32);
    aci_memset(ax86_frames, 0, ax86_frames_n / 32);
}

void ax86_page_set_directory (ax86_page_directory_t * page_directory)
{
    unsigned int cr0;
    asm volatile ("mov %0, %%cr3" :: "r" (&(dir->tables_physical_addr)));
    asm volatile ("mov %%cr0, %0" : "=r" (cr0));
    cr0 |= 0x80000000;
    asm volatile ("mov %0, %%cr0" :: "r" (cr0));
}

ax86_page_t * ax86_page_get (unsigned int address, ax86_page_directory_t * page_directory)
{
    unsigned int table_i;
    
    address /= ACI_PAGE_SIZE;
    
    table_i = address / 1024;
    if (page_directory->tables[table_i])
        return page_directory->tables[table_i]->pages[address % 1024];
    else {
        
