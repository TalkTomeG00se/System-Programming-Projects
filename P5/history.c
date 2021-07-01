#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "history.h"

static struct Cmd history[MAXHISTORY];

int historyNum = 0;  // Keeps track of history entries

void init_history(void) {   // Function to initialize the history array to track commands

	for (int i = 0; i < MAXHISTORY; i++) {

		history[i].cmd = malloc(MAX_LENGTH);  // Allocates memory for each cmd in the array, max # of any command is set at 1000
   
		memset(history[i].cmd, 0, MAXHISTORY);  // Allocating the block of memory
   
		history[i].exitStatus = 0; // Setting the exit status to 0 as default
	}

}

void add_history(char *cmd, int exitStatus) {  // Adds a command to the history array

	for (int i = 0; i < MAXHISTORY; i++) {

		if (history[i].cmd[0] == 0) {

			strncpy(history[i].cmd, cmd, MAX_LENGTH); // Makes a copy of the string and adds it to the array
      
			history[i].exitStatus = exitStatus; // Set new exitStatus to the one passed to the function
      
			return;
		}
	}

	for (int i = 0; i < MAXHISTORY - 1; i++) { // If at the end of the array

		strncpy(history[i].cmd, history[i + 1].cmd, MAX_LENGTH); // Copy and Shift
   
		history[i].exitStatus = history[i + 1].exitStatus; // Shift
	}
 
   strncpy(history[MAXHISTORY-1].cmd, cmd, MAX_LENGTH); // Copy and Shift
   
   history[MAXHISTORY -1].exitStatus = exitStatus;  // Shift
   
   historyNum++;  

}


void print_history(int firstSequenceNumber) {  // Prints the commands stored in the history array

	int first = firstSequenceNumber - historyNum - 1;
 
	if (first < 0 || first > MAXHISTORY) { // Checking to see if array is out of bounds

		first = 0;
	}

	for (int i = 0; i < MAXHISTORY; i++) { // Steps through array and prints out the commands in it

		if (history[i].cmd[0] != 0) {

			fprintf(stderr, "%d [%d] %s\n", i + 1 + historyNum, history[i].exitStatus, history[i].cmd);
		}
	}

}

void clear_history(void) {  // Clears the history arrow to avoid stranded memory

	for (int i = 0; i < MAXHISTORY ; i++) { // took out the minus 1, see what happens

		free(history[i].cmd); // Having random 'Wimplicit' warnings for this, still compiles and works, unknown reason.
	}

}