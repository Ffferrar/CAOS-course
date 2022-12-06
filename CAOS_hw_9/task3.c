//1. В цикле считываем имена файлов
//2. ПРоверяем файл на символическую ссылку - выводим абсолютное имя того файла, на который эта ссылка указывает

//3. ПРоверяем файл на регулярность - создаем симв ссылку в текущем каталоге
//чекнуть symlink, isreg+, realpath, sprintf

#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>

void zero_terminate(char *str);

int main(){
    char *file_name = calloc(PATH_MAX, sizeof(char));  
    char *path = calloc(PATH_MAX, sizeof(char));
    char *link = calloc(PATH_MAX, sizeof(char));
    
    struct stat meta_inf; 
    
     while (fgets(file_name, PATH_MAX, stdin) != NULL) {
     
     	zero_terminate(file_name);
     	
     	if (lstat(file_name, &meta_inf) == 0){
     	     	realpath(file_name, path);
     		if (S_ISLNK(meta_inf.st_mode)){
     			printf("%s\n", path);
     		}
     		
     		else if (S_ISREG(meta_inf.st_mode)){	
	     	    	sprintf(link, "link_to_%s", file_name);
	     	    	symlink(file_name, link);
     		}
     	}
     	
     }
     
     free(file_name);
}

void zero_terminate(char *str) {
    for (int i = 0;; ++i) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
}
