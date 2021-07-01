#include <stdio.h>
#include <string.h>
#include "history.h"
#include <stdlib.h>

static struct Cmd* hist;	
static int numHist = 0;	//counter for the number of history entries

void init_history(void) {			//Builds data structures for recording cmd history

	hist = (struct Cmd*) malloc(sizeof(struct Cmd) * MAXHISTORY);
}

void add_history(char *cmd, int exitStatus) {	// Adds a entry to history
	
	if (numHist >= MAXHISTORY) {
 
		free(hist[0].cmd);
		
		for (int i = 0; i < MAXHISTORY - 1; i++) { // Shifts everything down
   
			hist[i].cmd = hist[i+ 1].cmd;
      
			hist[i].exitStatus = hist[i + 1].exitStatus;

		}
		hist[MAXHISTORY - 1].cmd = cmd;
   
		hist[MAXHISTORY - 1].exitStatus = exitStatus;

	} else {

		hist[numHist].cmd = cmd;
   
		hist[numHist].exitStatus = exitStatus;

		numHist++;
	
	}
}

void clear_history(void) {			//Frees all allocated memory

	for (int i = 0; i < MAXHISTORY; i++) {
 
		free(hist[i].cmd);
	}
	
}

void print_history(int firstSequenceNumber) {	 // Prints history entries

	for (int i = 0; i < numHist; i++) {
 
		printf("%d [%d] %s\n", firstSequenceNumber++, hist[i].exitStatus, hist[i].cmd);
	}
}
