#ifndef filesystem_HEADER
#define filesystem_HEADER

#define FS_EOF 0

// for inode permissions
#define FS_READ    (1 << 1)
#define FS_WRITE   (1 << 2)

#define FS_MODE_WRITE  1
#define FS_MODE_READ   2
#define FS_MODE_APPEND 3

// for inode type, filedes type
#define FS_RAMDISK 0

// for filedes flags
#define FS_VALID (1 << 0)
#define FS_FILE  (1 << 1) /* not used */
#define FS_DIR   (1 << 2) /* not used */

#define FS_ERR_NOTFOUND 1
#define FS_ERR_MAKEFAIL 2
#define FS_ERR_BADPATH  3
#define FS_ERR_BADFDESC 4
#define FS_ERR_NOSPACE  5

typedef struct inode_s {
    unsigned char type;
    unsigned char permissions;
    unsigned int  filesize;
} inode_t;

typedef struct filesystem_calls_s {
    void * (* opendir)  (void *, char *);
    char * (* readdir)  (void *);
    int    (* closedir) (void *);
    int    (* mkdir)    (void *, char *);
    void * (* open)     (void *, char *, int mode);
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

extern int fs_errno;

int          fs_opendir  (char * path);
char *       fs_readdir  (int fd);
int          fs_closedir (int fd);
int          fs_mkdir    (char * path);
int          fs_open     (char * path, int oflag);
int          fs_close    (int fd);
unsigned int fs_write    (int fd, const void * buf, unsigned int nbyte);
unsigned int fs_read     (int fd, void * buf, unsigned int nbyte);

// splits a path into an array of strings
// the item after the last valid path will be NULL
// for /testing/filesystem/path would return
// {"testing", "filesystem", "path", NULL}
char ** filesystem_paths (char * path);

void    filesystem_paths_free (char ** paths);

#endif
