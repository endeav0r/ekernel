#ifndef page_HEADER
#define page_HEADER

#define ACI_MEM_SIZE  0x100000000
#define ACI_MEM_MIN   0x1000000
#define ACI_PAGE_SIZE 0x1000

#define AX86_PAGE_PRESENT  (1 << 0)
#define AX86_PAGE_WRITE    (1 << 1)
#define AX86_PAGE_USER     (1 << 2)
#define AX86_PAGE_ACCESSED (1 << 5)

typedef struct ax86_page_s {
    unsigned int present  : 1;
    unsigned int rw       : 1;
    unsigned int user     : 1;
    unsigned int accessed : 1;
    unsigned int dirty    : 1;
    unsigned int unused   : 7;
    unsigned int frame    : 20;
} ax86_page_t;

typedef struct ax86_page_table_s {
    ax86_page_t pages [1024];
} ax86_page_table_t;

typedef struct ax86_page_directory_s {
    page_table_t * tables [1024];
    unsigned int tables_physical [1024];
    unsigned int tables_physical_addr;
} ax86_page_directory_t;

void ax86_frame_set   (unsigned int address);
void ax86_frame_clear (unsigned int address);
int  ax86_frame_get   (unsigned int address);
int  ax86_frame_free  ();
int  ax86_frame_alloc (ax86_page_t * page, int user, int rw);
int  ax86_frame_free  (ax86_page_t * page);

void ax86_page_init ();
void ax86_page_set_directory (ax86_page_directory_t * page_directory);
#endif
