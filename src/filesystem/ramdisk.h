#ifndef ramdisk_HEADER
#define ramdisk_HEADER

#include "filesystem.h"
#include "../aci/config.h"

#define RAMDISK_NAME_SIZE 32

typedef struct ramdisk_node_s {
    inode_t inode;
    char name[RAMDISK_NAME_SIZE];
    unsigned int data_size;
    void * data;
    struct ramdisk_node_s * children;
    struct ramdisk_node_s * next;
} ramdisk_node_t;

typedef struct ramdisk_FILE_s {
    unsigned int position;
    ramdisk_node_t * node;
} ramdisk_FILE_t;

typedef struct ramdisk_DIR_s {
    ramdisk_node_t * child;
} ramdisk_DIR_t;

typedef struct ramdisk_s {
    ramdisk_node_t * nodes;
} ramdisk_t;

ramdisk_t     * ramdisk_create   ();

ramdisk_DIR_t * ramdisk_opendir  (ramdisk_t * ramdisk, char * path);
char *          ramdisk_readdir  (ramdisk_DIR_t * dir);
int             ramdisk_closedir (ramdisk_DIR_t * dir);
int             ramdisk_mkdir    (ramdisk_t * ramdisk, char * path);

ramdisk_FILE_t * ramdisk_open  (ramdisk_t * ramdisk, char * filename);
int              ramdisk_read  (ramdisk_FILE_t * fh, void * buf, int nbyte);
int              ramdisk_write (ramdisk_FILE_t * fh, const void * buf, int nbyte);
int              ramdisk_close (ramdisk_FILE_t * fh);

ramdisk_node_t * ramdisk_node_locate (ramdisk_t * ramdisk, char * path);
ramdisk_node_t * ramdisk_node_create ();

#endif
