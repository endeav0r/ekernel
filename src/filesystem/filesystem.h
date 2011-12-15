#ifndef filesystem_HEADER
#define filesystem_HEADER

// for inode permissions
#define FS_READ    (1 << 1)
#define FS_WRITE   (1 << 2)

// for inode type, filedes type
#define FS_RAMDISK 0

// for filedes flags
#define FS_VALID (1 << 0)

typedef struct inode_s {
    unsigned char type;
    unsigned char permissions;
} inode_t;

typedef struct filesystem_calls_s {
    void * (* opendir)  (void *, char *);
    char * (* readdir)  (void *);
    int    (* closedir) (void *);
    int    (* mkdir)    (void *, char *);
    void * (* open)     (void *, char *);
    int    (* read)     (void *, void *, int);
    int    (* write)    (void *, const void *, int);
    int    (* close)    (void *);
} filesystem_calls_t;

typedef struct filedes_s {
    unsigned char flags;
    unsigned char type;
    void * file;
} filedes_t;



void filesystem_init ();

int    fs_opendir  (char * path);
char * fs_readdir  (int fd);
int    fs_closedir (int fd);
int    fs_mkdir    (char * path);

// splits a path into an array of strings
// the item after the last valid path will be NULL
// for /testing/filesystem/path would return
// {"testing", "filesystem", "path", NULL}
char ** filesystem_paths (char * path);

void    filesystem_paths_free (char ** paths);

#endif
