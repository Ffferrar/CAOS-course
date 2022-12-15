#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <memory.h>
#include <sys/mman.h>


typedef struct Item {
    int value;
    uint32_t next_pointer;
} item_t;

uint32_t printer(item_t* x, char* map, uint32_t next_pointer);

int main(int argc, char *argv[]) {

    if (argc == 1){
    	return 0;
    }
    
    int input;
    if ((input = open(argv[1], O_RDONLY)) == -1) {
        return 1;
    }
    
    struct stat statistic;
    fstat(input, &statistic);
    
    uint32_t next_pointer = 0;
    
    if (statistic.st_size == 0){
        return 0;
    }
    
    char *map = mmap(NULL, statistic.st_size, PROT_READ, MAP_PRIVATE, input, 0);
    posix_madvise(map, statistic.st_size, POSIX_MADV_RANDOM);
    
    while (true){
    	item_t* x = (item_t*)(map + next_pointer);
    	next_pointer = printer(x, map, next_pointer);
    	
    	if (next_pointer == 0){
    		break;
    	}
    }
    munmap(map, statistic.st_size);
    close(input);
    return 0;
}

uint32_t printer(item_t* x, char* map, uint32_t next_pointer){

    next_pointer = x->next_pointer;
    printf("%d ", x->value);
       
    return next_pointer;

}
