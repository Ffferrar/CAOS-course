#include <inttypes.h>

#include <fcntl.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct Item {
    uint32_t next_pointer;
} item_t;

int main(int argc, char* argv[])
{
    char* input_file_name = argv[1];
    int fd = open(input_file_name, O_RDONLY, 0644);
    struct stat file_stats;
    fstat(fd, &file_stats);
    if (file_stats.st_size == 0)
        return 0;
        
    char* content_ptr =
        mmap(NULL, file_stats.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    posix_madvise(content_ptr, file_stats.st_size, POSIX_MADV_RANDOM);
    uint32_t next_pos = 0;
    uint32_t size_of_item = sizeof(item_t);
    
    
    while (1) {
        item_t* x = (item_t*)(content_ptr + next_pos);
        next_pos = x->next_pointer;
        printf("%d ", x->value);
        if (next_pos == 0)
            break;
    }
    
    
    munmap(content_ptr, file_stats.st_size);
    close(fd);
}
