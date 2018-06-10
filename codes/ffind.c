#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char **argv){

	DIR *fd;
	struct dirent *fp;

	fd=opendir(argv[1]);
	while((fp=readdir(fd)) != NULL){
		if(strncmp(fp->d_name,argv[2],strlen(argv[2])) >= 0) fprintf(stdout,"%s/%s\n",argv[1],fp->d_name);
	}
	return 0;
}
