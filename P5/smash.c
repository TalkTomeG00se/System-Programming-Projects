#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include "smash.h"
#include "history.h"


#define MAXLINE 4096

int main(int argc, char **argv) {

	init_history(); // Initializes the history to track commands

	char bfr[MAXLINE];

	fputs("$ ", stderr);

	while (fgets(bfr, MAXLINE, stdin) != NULL) {

		bfr[strlen(bfr) - 1] = '\0';

		if (strcmp(bfr, "exit") == 0) {

			clear_history(); // Upon exit, clears all allocated memory

			exit(0);

		}
		if (executeCommand(&bfr[0]) == 1) {

			fflush(stdout);
      
			int pid = fork();

			if (pid == 0) {

				int exit = externalCommand(&bfr[0]);

				if (exit == -1) {

					int exitStatus = 127;

					printf("Invalid command.\n");
                          
					fflush(stdout);
     
					return exitStatus;
                 
				}

			}
			else if (pid > 0) {

				fflush(stdout);

				int exitStatus;

				wait(&exitStatus);
        
        fputs("$ ", stderr);

			}
			else {

				perror("Fork failed");

			}
		}
	}

	fputs("$ ", stderr);


return 0;

}