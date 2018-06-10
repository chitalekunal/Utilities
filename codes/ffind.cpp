#include <cstdio>
#include <regex>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <dirent.h>


using namespace std;

int main(int argc, char **argv){

	DIR *fd;
	struct dirent *fp;

	string path=string(argv[1]);
	string find_string=string(argv[2]);
	fd=opendir(path.c_str());
	while((fp=readdir(fd)) != NULL){

		if (regex_match(string(fp->d_name),regex(find_string))){
			fprintf(stdout,"%s/%s\n",path.c_str(),fp->d_name);
		}


//		if(strncmp(fp->d_name,find_string.c_str(),find_string.length()) >= 0) fprintf(stdout,"%s/%s\n",argv[1],fp->d_name);
	}
	return 0;
}
