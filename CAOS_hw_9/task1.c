#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

void zero_terminate(char *str);
void checking_ELF(int input, char *file_name );
int short_major(int input, char *file_name );

int main() {
        char *file_name = calloc(PATH_MAX, sizeof(char));   
	struct stat meta_info;
	char *nl;
	while (fgets(file_name, PATH_MAX, stdin) != NULL) {
		zero_terminate(file_name);

		int input = open(file_name, O_RDONLY);

		if (input > 0 && fstat(input, &meta_info) != -1 && meta_info.st_mode & S_IXUSR) {
			if (lseek(input, 0, SEEK_END) < 2){
				puts(file_name); 
				continue;
			}
			if (!short_major(input, file_name)){
				checking_ELF(input, file_name);	
			}
			else{ continue; }
		}
	}
	
	free(file_name);
	return 0;
}

void zero_terminate(char *str) {
    for (int i = 0;; ++i) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
}

int short_major(int input, char *file_name ){
	lseek(input, 0, SEEK_SET);
	char hash= -1;
	char exclamation = -1;
	read(input, &hash, sizeof(char));
	read(input, &exclamation, sizeof(char));
	
	if (exclamation == '!' && hash == '#') {
                char buffer[PATH_MAX];
                read(input, buffer, sizeof(buffer));
                char *meme = memchr(buffer, '\n', sizeof(buffer));
                if (meme) {*meme = '\0';}
                struct stat interpreter;
                if (stat(buffer, &interpreter) == -1 || !(interpreter.st_mode & S_IXUSR)){
                	puts(file_name);
                }
                return 1;
            } 
            
            else{ return 0; }
}

void checking_ELF(int input, char *file_name ){

	char data[4];
	FILE *file = fopen(file_name, "r");

	fgets(data, 4, file);
	fclose(file);

	if (data[0] == 0x7f && data[1] == 'E' && data[2] == 'L' && data[3] == 'F'){ 
		puts(file_name);
	}
}
