#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "history.h"

int executeCommand(char *str) {

	char newString[MAX_LENGTH];

	strncpy(newString, str, strlen(str));

	newString[strlen(str)] = 0;

	char* token = strtok(str, " ");

	if (strcmp(token, "cd") == 0) {

		token = strtok(NULL, " ");

		if (chdir(token) == -1) {

			add_history(newString, 1); // If the cd command fails

			fprintf(stderr, "%s: 'No such file or directory'\n", token);
		}
		else
		{
			add_history(newString, 0); // If the cd command works

			printf("%s\n", token);
		}
	}
	else if (strcmp(token, "history") == 0)  // If the token is history, invoke the print_history function
	{
		token = strtok(NULL, " ");
		
		if (token != NULL)
		{

			print_history(atoi(token)); // Converts the token string to a int value in the print_history function, which is passed an int

		}
		else
		{
      
			print_history(0);

		}

		add_history(newString, 0); 
   
	}
	else
	{

		add_history(newString, 127); // Anyting that isn't the cd or history command

		while (token != NULL)
		{

			token = strtok(NULL, " ");
		}
   
	}
  return 1; 
}

int externalCommand(char *str ){ // Added this whole function

  char *extCmd[1024];
  
  char *token = strtok(str, " ");
  
  char *command = token;
  
  int counter = 0;
  
  while(token != NULL){
  
    extCmd[counter] = token;
    
    counter++;
    
    token = strtok(NULL, " ");
  
  }
  
  extCmd[counter] = NULL;
  
  if((execvp(command, extCmd) == -1)){ // History is returning a value of -1
  
    return -1;
  
  }
  
  return 0;

}