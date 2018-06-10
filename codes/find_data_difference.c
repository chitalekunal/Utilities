#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc,char **argv)
{


	// Check if all the parameters are provided by the user
	if (argc < 7){
		fprintf(stderr, "Incorrect Format\n\nPlease provide following parameters in following sequence\n\n\tfile_difference <filename1> <file1 columns delimiter> <file1 record delimiter> <filename2> <file2 column delimiter> <file2 record delimiter>\n\n");
		exit(1);
	}

	//Initialize file and buffer variables
	FILE *fd1, *fd2;
	char *fd1_buffer, *fd2_buffer;
	int fd1_end,fd2_end,memsize1,memsize2;

	//Open files for reading
	fd1 = fopen(argv[1],"r");
	if (fd1 == 0 ) {
		perror("Incorrect Filename at position 1");
		exit(1);
	}
	fd2 = fopen(argv[4],"r");
	if (fd2 == 0){
		perror("incorrect Filename at position 4");
		exit(1);
	}
	
	fd1_end = fseek(fd1,0,SEEK_END);
	fd2_end = fseek(fd2,0,SEEK_END);

	memsize1=((fd1_end/30) < 1073741824 ? fd1_end/30 : 1073741824 ;
	memsize2=((fd2_end/30) < 1073741824 ? fd_end/30 : 1073741824;

	printf("%d,%d",memsize1,memsize2);
}
