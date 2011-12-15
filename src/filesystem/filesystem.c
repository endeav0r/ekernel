#include "filesystem.h"

#include "ramdisk.h"
#include "../common/error.h"
#include "../common/debug.h"

#include "../aci/stdlib/stdlib.h"

#define FILESYSTEM_FILEDES_MAX 8

filesystem_calls_t fs_calls[1];
filedes_t fs_filedes[FILESYSTEM_FILEDES_MAX];

void * filesystem_root;

void filesystem_init ()
{
    DEBUG_STACK_TRACE("filesystem_init")

    int i;

    aci_vga_write("init filesystem calls\n");

    // they said, "you can't cast those function pointers. that's crazy talk."
    // i said, "good think C programmers laugh in the face of crazy."
    // they said, "bad C programmers."
    fs_calls[FS_RAMDISK].opendir  =
     (void * (* ) (void *, char *)) ramdisk_opendir;
    fs_calls[FS_RAMDISK].readdir  =
     (char * (* ) (void *)) ramdisk_readdir;
    fs_calls[FS_RAMDISK].closedir = 
     (int (* ) (void *)) ramdisk_closedir;
    fs_calls[FS_RAMDISK].mkdir    =
     (int (* ) (void *, char *)) ramdisk_mkdir;

    for (i = 0; i < FILESYSTEM_FILEDES_MAX; i++)
        aci_memset(&(fs_filedes[i]), 0, sizeof(filedes_t));
    
    aci_vga_write("create root ramdisk\n");
    filesystem_root = ramdisk_create();

    aci_vga_write("filesystem init done\n");
}

int fs_opendir (char * path)
{
    DEBUG_STACK_TRACE("fs_opendir")

    int fd;

    for (fd = 0; fd < FILESYSTEM_FILEDES_MAX; fd++) {
        if ((fs_filedes[fd].flags & FS_VALID) == 0)
            break;
    }

    if (fd < FILESYSTEM_FILEDES_MAX) {
        fs_filedes[fd].file =
         fs_calls[FS_RAMDISK].opendir(filesystem_root, path);
        if (fs_filedes[fd].file == NULL)
            return -1;
        fs_filedes[fd].flags = FS_VALID;
        fs_filedes[fd].type = FS_RAMDISK;
        return fd;
    }

    return -2;
}

char * fs_readdir (int fd)
{
    DEBUG_STACK_TRACE("fs_readdir")

    if ((fs_filedes[fd].flags & FS_VALID) == 0) {
        errno = FILESYSTEM_BAD_FD;
        return NULL;
    }
    return fs_calls[fs_filedes[fd].type].readdir(fs_filedes[fd].file);

}

int fs_closedir (int fd)
{
    DEBUG_STACK_TRACE("fs_closedir")

    if ((fs_filedes[fd].flags & FS_VALID) == 0) {
        errno = FILESYSTEM_BAD_FD;
        return -1;
    }
    fs_filedes[fd].flags = 0;
    return fs_calls[fs_filedes[fd].type].closedir(fs_filedes[fd].file);
}

int fs_mkdir (char * path)
{
    DEBUG_STACK_TRACE("fs_mkdir")

    return fs_calls[FS_RAMDISK].mkdir(filesystem_root, path);
}

char ** filesystem_paths (char * path)
{
    DEBUG_STACK_TRACE("filesystem_paths")

    int i;
    int items = 0;
    int item_i;
    int item_size;
    // how many path items are there

    if (path[0] == '/')
        path = &(path[1]);

    for (i = 0; i < aci_strlen(path); i++) {
        if (path[i] == '/')
            items++;
    }

    char ** paths = (char **) aci_malloc(sizeof(char *) * (items + 1));

    i = 0;
    item_i = 0;
    while (i < aci_strlen(path)) {
        // get size of this item
        for (item_size = i; item_size < aci_strlen(path); item_size++) {
            if (path[item_size] == '/')
                break;
        }
        item_size -= i;

        paths[item_i] = (char *) aci_malloc(item_size + 1);
        aci_strncpy(paths[item_i], &(path[i]), item_size);
        paths[item_i][item_size] = '\0';
        item_i++;
        i += item_size + 1;
    }

    paths[item_i] = NULL;
    return paths;
}

void filesystem_paths_free (char ** paths)
{
    DEBUG_STACK_TRACE("filesystem_paths_free")

    int path_i = 0;
    while (paths[path_i] != NULL) {
        if (aci_free(paths[path_i]))
            debug_panic("freeing path");
        path_i++;
    }
    if (aci_free(paths))
        debug_panic("freeing paths");
}
