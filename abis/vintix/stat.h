#ifndef _ABIBITS_STAT_H
#define _ABIBITS_STAT_H

#include <abi-bits/off_t.h>
#include <abi-bits/time_t.h>
#include <abi-bits/mode_t.h>
#include <abi-bits/ino_t.h>
#include <abi-bits/dev_t.h>
#include <abi-bits/uid_t.h>
#include <abi-bits/gid_t.h>
#include <abi-bits/blksize_t.h>
#include <abi-bits/blkcnt_t.h>

struct stat {
    dev_t st_dev;
    ino_t st_ino;
    mode_t st_mode;
    nlink_t st_nlink;
    uid_t st_uid;
    gid_t st_gid;
    off_t st_size;
    time_t st_mtime;
    blksize_t st_blksize;
    blkcnt_t st_blocks;
};

enum {
    // Type of file
    S_IFBLK = 1,  // Block special
    S_IFCHR = 2,  // Character special
    S_IFIFO = 3,  // FIFO special
    S_IFREG = 4,  // Regular
    S_IFDIR = 5,  // Directory
    S_IFLNK = 6,  // Symbolic link
    S_IFSOCK = 7, // Socket

    // File mode bits
    S_IXOTH = 00001,                       // Execute/search permission (others)
    S_IWOTH = 00002,                       // Write permission (others)
    S_IROTH = 00004,                       // Read permission (others)
    S_IRWXO = S_IXOTH | S_IWOTH | S_IROTH, // Read, write, execute (others)
    S_IXGRP = 00010,                       // Execute/search permission (group)
    S_IWGRP = 00020,                       // Write permission (group)
    S_IRGRP = 00040,                       // Read permission (group)
    S_IRWXG = S_IXGRP | S_IWGRP | S_IRGRP, // Read, write, execute (group)
    S_IXUSR = 00100,                       // Execute/search permission (owner)
    S_IWUSR = 00200,                       // Write permission (owner)
    S_IRUSR = 00400,                       // Read permission (owner)
    S_IRWXU = S_IXUSR | S_IWUSR | S_IRUSR, // Read, write, execute (owner)
    S_ISUID = 0004000,                     // Set user UID on execution
    S_ISGID = 0002000,                     // Set group ID on execution
    S_ISVTX = 0001000                      // Sticky bit
};

#define S_ISBLK(m) ((m) == S_IFBLK)
#define S_ISCHR(m) ((m) == S_ISCHR)
#define S_ISDIR(m) ((m) == S_ISDIR)
#define S_ISFIFO(m) ((m) == S_ISFIFO)
#define S_ISREG(m) ((m) == S_ISREG)
#define S_ISLNK(m) ((m) == S_ISLNK)
#define S_ISSOCK(m) ((m) == S_ISSOCK)

#endif // _ABIBITS_STAT_H
