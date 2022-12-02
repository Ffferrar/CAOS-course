#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <windows.h>

DWORD printer(HANDLE input, int value, DWORD curr_pos, DWORD next_pointer);

int main(int argc, char *argv[]) {

    if (argc == 1){
    	return 0;
    }
       
    HANDLE input;
    if ((input = CreateFileA(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL,
    OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE) {
        return 1;
    }
    
    DWORD next_pointer = 0;
    int value = 0;
    DWORD curr_pos = -1;
    
    while (curr_pos != 0){
    	curr_pos = printer(input, value, curr_pos, next_pointer);
    }
    DeleteFileA(argv[1]);
    CloseHandle(input);
    return 0;
}

DWORD printer(HANDLE input, int value, DWORD curr_pos, DWORD next_pointer){
    
    DWORD bytes = 0;   
    ReadFile(input, &value, sizeof(value), &bytes, NULL); 
    ReadFile(input, &next_pointer, sizeof(next_pointer), NULL, NULL);
    
    if (bytes == 0) {
	return 0;
    }	
    
    printf("%d ", value);
    curr_pos = SetFilePointer(input, next_pointer, NULL, FILE_BEGIN);

   
    return curr_pos;
}
