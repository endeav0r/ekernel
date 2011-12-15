#include "ramdisk.h"

#define RAMDISK_DEBUG

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
    node->data_size = 0;
    node->data = NULL;
    node->children = NULL;
    node->next = NULL;

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
        return NULL;
    }
    dir->child = dir->child->children;

    return dir;
}

char * ramdisk_readdir (ramdisk_DIR_t * dir)
{
    DEBUG_STACK_TRACE("ramdisk_readdir")

    char * filename;

    if (dir->child == NULL)
        return NULL;
    
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
    for (i = aci_strlen(path); i > 0; i--) {
        if (path[i] == '/')
            break;
    }

    // remember i includes '/'
    parent_path = aci_malloc(i);
    aci_strncpy(parent_path, path, i - 1);

    // get parent node
    parent_node = ramdisk_node_locate(ramdisk, parent_path);
    aci_free(parent_path);
    if (parent_node == NULL)
        return -1;
    
    node = ramdisk_node_create();
    aci_strncpy(node->name, &(path[i+1]), RAMDISK_NAME_SIZE);
    node->name[RAMDISK_NAME_SIZE - 1];
    node->next = parent_node->children;
    parent_node->children = node;

    return 0;
}

