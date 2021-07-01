#define _POSIX_C_SOURCE 200809L // fixes strdup warnings
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "history.h"
#include "smash.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

static int count = 0;

static int first;

static char* stringCopy;

int externalCommand(char* commands[1024]) { // Commands that bash can execute via execvp

	int pid = fork();

	if (pid == 0) { // Command doesn't exit

		execvp(commands[0], commands);

		perror(commands[0]);

		exit(127);
	}
	else if (pid > 0) { // Command exists 

		int exitStatus;

		wait(&exitStatus);

		if (exitStatus != -1) {

			return 127;
		}
		else {

			return exitStatus;
		}
	}
	else {

		fprintf(stderr, "Failure to Fork.\n");
	}

	return -1;
}


int executeCommand(char* str) {

	char* args[1000];

	char* token = strtok(str, " ");

	int i = 0;

	while (token != NULL) {

		args[i] = token;

		i++;

		token = strtok(NULL, " ");
	}
	args[i] = NULL;


	if (strcmp(args[0], "exit") == 0) { // If exit command

		clear_history();

		exit(0);
	}
	else if (strcmp(args[0], "cd") == 0) { // If cd command

		if (i == 2) {

			int cdir = chdir(args[1]);

			if (cdir != 0) { // directory doesn't exist

				add_history(stringCopy, 1);

				perror(args[i]);

				return -1;
			}
			else {

				add_history(stringCopy, 0);

				fprintf(stdout, "%s\n", args[1]);

				return 0;
			}
		}
	}
	else if (strcmp(args[0], "history") == 0) { // If history command

		print_history(first);

		add_history(stringCopy, 0);

		return 0;


	}
	else { // Not internal commands cd, history, exit

		int command = externalCommand(args);

		add_history(stringCopy, command);

		return command;
	}

	return 0;
}

int redirCheck(char* input, char* filename) {

	for (int i = 0; i < strlen(input); i++) {
 
		if (input[i] == '<') {
   
			input[i] = '\0';
      
			while (input[i+1] == ' ') {
      
				i++;
			}
			
		
			while (input[i+1] == ' ') { // Leading whitespace trim
      
				i++;
			}
			strncat(filename, &input[i+1], strlen(&input[i+1]));

			
			for (int j = 0; j < strlen(filename); j++) {// Trailing whitespace trim
      
				if (filename[j] == ' ') {
        
					filename[j] = '\0';
				}
			}
		
			return 1;
		}
		
		if (input[i] == '>') {
   
			input[i] = '\0';
		
			
			while (input[i+1] == ' ') {
				i++;
			}
			strncat(filename, &input[i+1], strlen(&input[i+1]));
		
		
			for (int j = 0; j < strlen(filename); j++) {
      
				if (filename[j] == ' ') {
        
					filename[j] = '\0';
				}
			}
		
			return 2;
		}
	}
	return -1;
}


int allCommands(char* str) {

	char file[1024];

	int direction = redirCheck(str, file);

	if (direction == 2) { // out

		int outDirect = open(file, O_RDONLY, 0600);

		int stdinCopy = dup(0);

		close(0);

		dup2(outDirect, 0);

		int exitStatus = executeCommand(str);

		dup2(stdinCopy, 0);

		close(stdinCopy);

		return exitStatus;

	}
	else if (direction == 1) { // In

		int inDirect = open(file, O_CREAT | O_RDWR, 0600);

		int stdoutCopy = dup(1);

		close(1);

		dup2(inDirect, 1);

		close(inDirect);

		int exitStatus = executeCommand(str);

		dup2(stdoutCopy, 1);

		close(stdoutCopy);

		return exitStatus;

	}
	else {

		int exitStatus = executeCommand(str);

		return exitStatus;
	}

	// Flushing output to console
	fflush(stdin);

	fflush(stdout);

	for (int i = 0; i < strlen(file); i++) {

		file[i] = '\0';
	}
}

void shellStart(char* str) {


	first = 1; // Cannot be zero, doubling history entries

	if (first >= MAXHISTORY) { // Sets up the history

		first = count - MAXHISTORY + 1;
	}
	count++;

	stringCopy = strndup(str, strlen(str));		// copy of the command string

	char* pipes[1024];

	char* token = strtok(str, "|"); // Checking for the pipe symbol

	int index = 0;

	while (token != NULL) {

		pipes[index] = token;

		index++;

		token = strtok(NULL, "|");
	}
	pipes[index] = NULL;

	int numCommands = index;

	int pipeCount = numCommands - 1;

	static int exitStatus;

	if (pipeCount == 0) { // No pipes in str

		exitStatus = allCommands(pipes[0]);
	}
	else {

		int newPipe[2 * pipeCount]; // Giving problems, says its not constant

		for (int i = 0; i < pipeCount; i++) {

			pipe(&newPipe[2 * i]); // creates the pipes
		}


		for (int i = 0; i < numCommands; i++) {

			int child = fork();

			if (child < 0) { // fork failed

				fprintf(stderr, "Failure to fork.\n");

				exit(-1);
			}
			else if (child == 0) {

				if (i == 0) {

					close(newPipe[0]); // Closes the out pipe

					dup2(newPipe[1], 1);


					for (int j = 2; j < pipeCount * 2; j++) { // Closes unused pipes

						close(newPipe[j]);

					}
					exitStatus = allCommands(pipes[i]);


					close(newPipe[1]); // Closes inlet pipe

				}
				else if (i + 1 == numCommands) {


					int inLocation = (i - 1) * 2;

					dup2(newPipe[inLocation], 0);

					for (int j = 0; j < pipeCount * 2; j++) {

						if (j != inLocation) {

							close(newPipe[j]);
						}
					}

					exitStatus = allCommands(pipes[i]);

					close(newPipe[inLocation]);

				}
				else {

					int inLocation = (i - 1) * 2;

					int outLocation = inLocation + 3;

					dup2(newPipe[inLocation], 0);

					dup2(newPipe[outLocation], 1);

					for (int j = 0; j < pipeCount * 2; j++) {

						if (j != inLocation && j != outLocation) {

							close(newPipe[j]);
						}
					}

					exitStatus = allCommands(pipes[i]);

					close(newPipe[inLocation]);

					close(newPipe[outLocation]);

				}

				exit(exitStatus);
			}


		}

		for (int i = 0; i < pipeCount * 2; i++) {

			close(newPipe[i]);
		}
		for (int i = 0; i < numCommands; i++) {

			wait(&exitStatus);
		}

		if (exitStatus != -1) {

			exitStatus = 127;
		}
		add_history(stringCopy, exitStatus);
	}
}


#define MAXLINE 4096

int main(int argc, char** argv) {

	init_history(); // Initializes the history to track commands

	char bfr[MAXLINE];

	fputs("$ ", stderr);

	while (fgets(bfr, MAXLINE, stdin) != NULL) {

		bfr[strlen(bfr) - 1] = '\0';

		if (strlen(bfr) != 0) {

			shellStart(bfr);
		}

		fputs("$ ", stderr);

	}

	return 0;

}