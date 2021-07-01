#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "smash.h"


#define MAXLINE 4096

int main(int argc, char **argv) {

	char bfr[MAXLINE];   

	fputs("$ ",stderr);

	while (fgets(bfr, MAXLINE, stdin) != NULL) {

		bfr[strlen(bfr) - 1] = '\0';
   
    if(strcmp(bfr,"exit") == 0) {
    
      exit(0);
    }
    
    executeCommand(&bfr[0]);

		fputs("$ ", stderr);

	}
	return 0;
}

