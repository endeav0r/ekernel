#include "ramdisk.h"

// #define RAMDISK_DEBUG

#include "../common/debug.h"
#include "filesystem.h"
#include "../aci/stdlib/stdlib.h"

ramdisk_t * ramdisk_create ()
{
    DEBUG_STACK_TRACE("ramdisk_create")

    ramdisk_t * ramdisk;

    #ifdef RAMDISK_DEBUG
        char buf[32];
        aci_vga_write("ramdisk_create ");
    #endif

    ramdisk = aci_malloc(sizeof(ramdisk_t));
    #ifdef RAMDISK_DEBUG
        aci_sprintf(buf, "(%x) ", ramdisk);
        aci_vga_write(buf);
    #endif

    ramdisk->nodes = ramdisk_node_create();
    #ifdef RAMDISK_DEBUG
        aci_sprintf(buf, "(%x) ", ramdisk->nodes);
        aci_vga_write(buf);
    #endif


    return ramdisk;
}

ramdisk_node_t * ramdisk_node_locate (ramdisk_t * ramdisk, char * path)
{
    DEBUG_STACK_TRACE("ramdisk_node_locate")

    int path_i;
    ramdisk_node_t * node;
    ramdisk_node_t * child;
    char ** paths;
    
    #ifdef RAMDISK_DEBUG
        char buf[32];
        aci_vga_write("ramdisk_node_locate ");
    #endif
    paths = filesystem_paths(path);

    node = ramdisk->nodes;
    path_i = 0;

    #ifdef RAMDISK_DEBUG
        aci_sprintf(buf, "(%x) ", paths);
        aci_vga_write(buf);
        aci_vga_write("1 ");
    #endif
    while (node != NULL) {
        #ifdef RAMDISK_DEBUG
            aci_vga_write("2 ");
        #endif
        if (paths[path_i] == NULL)
            break;
        for (child = node->children; child != NULL; child = child->next) {
            #ifdef RAMDISK_DEBUG
                aci_vga_write("3 ");
            #endif
            if (aci_strcmp(paths[path_i], child->name) == 0) {
                node = child;
                path_i++;
                break;
            }
        }
        if (child == NULL)
            node = NULL;
    }

    #ifdef RAMDISK_DEBUG
        aci_vga_write("4 ");
    #endif
    filesystem_paths_free(paths);
    #ifdef RAMDISK_DEBUG
        aci_vga_write("5\n");
    #endif

    return node;
}

ramdisk_node_t * ramdisk_node_create ()
{
    DEBUG_STACK_TRACE("ramdisk_node_create")

    ramdisk_node_t * node;

    node = aci_malloc(sizeof(ramdisk_node_t));
    aci_memset(node->name, 0, RAMDISK_NAME_SIZE);
    node->data_size         = 0;
    node->data              = NULL;
    node->children          = NULL;
    node->next              = NULL;
    node->inode.type        = FS_RAMDISK;
    node->inode.permissions = FS_READ | FS_WRITE;
    node->inode.filesize    = 0;

    return node;
}

ramdisk_DIR_t * ramdisk_opendir (ramdisk_t * ramdisk, char * path)
{
    DEBUG_STACK_TRACE("ramdisk_opendir")

    ramdisk_DIR_t * dir;

    dir = aci_malloc(sizeof(ramdisk_DIR_t));
    dir->child = ramdisk_node_locate(ramdisk, path);
    if (dir->child == NULL) {
        aci_free(dir);
        fs_errno = FS_ERR_NOTFOUND;
        return NULL;
    }
    dir->child = dir->child->children;

    return dir;
}

char * ramdisk_readdir (ramdisk_DIR_t * dir)
{
    DEBUG_STACK_TRACE("ramdisk_readdir")

    char * filename;

    if (dir->child == NULL) {
        fs_errno = FS_ERR_BADFDESC;
        return NULL;
    }
    
    filename = dir->child->name;
    dir->child = dir->child->next;

    return filename;
}

int ramdisk_closedir (ramdisk_DIR_t * dir)
{
    DEBUG_STACK_TRACE("ramdisk_closedir")

    aci_free(dir);
}

int ramdisk_mkdir (ramdisk_t * ramdisk, char * path)
{
    DEBUG_STACK_TRACE("ramdisk mkdir")

    int i;
    char * parent_path;
    ramdisk_node_t * parent_node;
    ramdisk_node_t * node;

    // find parent directory path
    for (i = aci_strlen(path) - 1; i >= 0; i--) {
        if (path[i] == '/')
            break;
    }

    // if path[i] doesn't include a '/', no parent directory path given
    if (path[i] != '/') {
        aci_vga_write("no parent directory path given\n");
        fs_errno = FS_ERR_BADPATH;
        return -1;
    }

    parent_path = aci_malloc(i + 1);
    aci_strncpy(parent_path, path, i);

    // get parent node
    parent_node = ramdisk_node_locate(ramdisk, parent_path);
    aci_free(parent_path);
    if (parent_node == NULL) {
        aci_vga_write("could not find parent node: ");
        aci_vga_write(parent_path);
        aci_vga_write("\n");
        fs_errno = FS_ERR_NOTFOUND;
        return -1;
    }
    
    node = ramdisk_node_create();
    aci_strncpy(node->name, &(path[i+1]), RAMDISK_NAME_SIZE);
    node->name[RAMDISK_NAME_SIZE - 1];
    node->next = parent_node->children;
    parent_node->children = node;

    return 0;
}

ramdisk_FILE_t * ramdisk_open (ramdisk_t * ramdisk, char * filename, int mode)
{
    ramdisk_FILE_t * fh;

    fh = (ramdisk_FILE_t *) aci_malloc(sizeof(ramdisk_FILE_t));
    fh->position = 0;
    fh->mode = mode;
    fh->node = ramdisk_node_locate(ramdisk, filename);

    // file doesn't exist, opening for write or append
    if (    (fh->node == NULL) 
         && ((mode == FS_MODE_WRITE) || (mode == FS_MODE_APPEND))) {
        // files and directories are same thing, so we're going to cheat here
        if (ramdisk_mkdir(ramdisk, filename) != 0) {
            aci_free(fh);
            // fs_errno set by ramdisk_mkdir
            return NULL;
        }
        fh->node = ramdisk_node_locate(ramdisk, filename);
    }
    // file exists, opening for write
    else if (mode == FS_MODE_WRITE) {
        if (fh->node->data != NULL)
            aci_free(fh->node->data);
        fh->node->data = NULL;
        fh->node->data_size = 0;
        fh->node->inode.filesize = 0;
    }
    // file exists, opening for append
    else if (mode == FS_MODE_APPEND) {
        fh->position = fh->node->inode.filesize;
    }
    else if (fh->node == NULL) {
        aci_free(fh);
        fs_errno = FS_ERR_NOTFOUND;
        return NULL;
    }

    return fh;
}

int ramdisk_close (ramdisk_FILE_t * fh)
{
    aci_free(fh);

    return 0;
}

unsigned int ramdisk_write (ramdisk_FILE_t * fh, const void * buf, unsigned int nbyte)
{
    ramdisk_node_t * node;
    void * data_realloc;

    node = fh->node;

    if (fh->position + nbyte > node->data_size) {
        data_realloc = aci_realloc(node->data, fh->position + nbyte +
                                               RAMDISK_WRITE_SCRATCH);
        if (data_realloc == NULL) {
            fs_errno = FS_ERR_NOSPACE;
            return -1;
        }
        node->data_size = fh->position + nbyte + RAMDISK_WRITE_SCRATCH;
        node->data = data_realloc;
    }

    aci_memcpy(&(node->data[fh->position]), buf, nbyte);
    fh->position += nbyte;

    return nbyte;
}

unsigned int ramdisk_read (ramdisk_FILE_t * fh, void * buf, unsigned int nbyte)
{
    // at the end of the file
    if (fh->position == fh->node->inode.filesize)
        return FS_EOF;

    // if we can't fill the entire buffer
    if (fh->node->inode.filesize < fh->position + nbyte) {
        aci_memcpy(buf,
                   &(fh->node->data[fh->position]),
                   fh->node->inode.filesize - fh->position);
        fh->position = fh->node->inode.filesize;
        return fh->node->inode.filesize - fh->position;
    }

    aci_memcpy(buf, &(fh->node->data[fh->position]), nbyte);
    fh->position += nbyte;
    return nbyte;
}
