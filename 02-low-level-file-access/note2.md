# 02 - Low-level File Access (sys call)

File descriptor : Abstract key or a reference for accessing the file

- `0 : stdin`  : standard input
- `1 : stdout` : standard output
- `2 : stderr` : standard error

## Libraries used

* `#include <fcntl.h>` : for file descriptors
* `#include <sys/types.h>`
* `#include <sys/stat.h>`
* `#include <unistd.h>` : for file operations

## Syntax
### `open()`

- `int open(char* filePath, int oflags);`

- `int open(char* filePath, int oflags, mode_t mode);`

    * return
        - `-1` : error
        - `file descriptor` : success

```c
int open = open("file", O_WRONLY | OCREAT, S_IRUSR | S_IWUSR);
```

* mandatory oflags
    - **O_RDONLY** : read-only
    - **O_WRONLY** : write-only
    - **O_RDWR** : read and write
    * opetionals
        - **O_APPEND** : append to the existing data in the file
        - **O_TRUNC** : override the existing data in the file
        - **O_CREAT** : if file does not exist, create it(with given permissions)
        - **O_EXCL** : use with O_CREAT to ensure that the file is open for just only this functioning program
* permisstion flags
    - used to defined the permission for each previllege group of users. 
        *  USER : **S_IRUSR, S_IWUSR, S_IXUSR**
        *  GROUP : **S_IRGRP, S_IWGRP, S_IXGRP**
        *  OTHERS : **S_IROTH, S_IWOTH, S_IXOTH**
    - This is the similar concept as linux file permission and we can represent each flag as octal e.g. `int open = open("file", O_WRONLY | OCREAT, 0666);` 0666 is to give permission read and write to users, groups and all others

### `write()`
- `size_t write(int fileDescriptor, const void* buffer, size_t countBytes);`

    * return
        - `-1` : error
        - `numbers of bytes written` : success

```c
write(1, "Some data is written\n", 21);
```
Here, 1 is the file descriptor for stdout.
```c
write(2, "An error has occurred on the stdout\n", 36);
```
Here, 2 is the file descriptor for stderr.

### `read()`
- `size_t read(int fileDescriptor, void* buf, size_t countBytes);`

    * return
        - `-1` : error
        - `0` : EOF (end of file)
        - `number of bytes read` : success

```c
int nread;
char buffer[120];

nread = read(0, buffer, 120);
```
Here, 0 is the file descriptor stdin, and we specified size of buffer to be 120 bytes.

### `close()`
- `int close(int fileDescriptor);`
    * return 
        - `-1` : error
        - `0` : success
```c
int open;

open = open("file", O_RDONLY);
close(open);
```
### `lseek()`
 read/write pointer in file descriptor used to set the location in the file.
 * `off_t lseek(int fileDescriptor, off_t offest, int whence);`
    - whence specifiers used to set the **references (starting point)** of the cursor
        - **SEEK_SET** : beggining of the file
        - **SEEK_CUR** : current position
        - **SEEK_END** : end of file
```c
lseek(out, 8, SEEK_SET);
```