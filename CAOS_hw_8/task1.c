#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

off_t printer(int input, int value, off_t curr_pos, uint32_t next_pointer);

int main(int argc, char *argv[]) {

    if (argc == 1){
    	return 0;
    }
       
    int input;
    if ((input = open(argv[1], O_RDONLY)) == -1) {
        return 1;
    }
    
    uint32_t next_pointer = 0;
    int value = 0;
    off_t curr_pos = -1;
    
    while (curr_pos != 0){
    	curr_pos = printer(input, value, curr_pos, next_pointer);
    }
    
    close(input);
    return 0;
}

off_t printer(int input, int value, off_t curr_pos, uint32_t next_pointer){
       
    ssize_t val = read(input, &value, sizeof(value));
    ssize_t next_val = read(input, &next_pointer, sizeof(next_pointer));
       
    if (val <= 0){
   	return 0;
    }
   
    if (next_val <= 0){
   	next_pointer = 0;
    }
    
    printf("%d ", value);
    curr_pos = lseek(input, next_pointer, SEEK_SET);   
   
    return curr_pos;
}
