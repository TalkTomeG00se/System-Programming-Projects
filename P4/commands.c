#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "smash.h"

void executeCommand(char *str) {

	char* token = strtok(str, " ");
 
  if(strcmp(token, "cd") == 0){
  
   token = strtok(NULL," ");
   
   if(chdir(token) == -1) {
   
     fprintf(stderr, "%s: 'No such file or directory'\n", token);
     
   } else {
   
     printf("%s\n",token);
   
   }
   
   
  } else {
 
  int i=0;

	while (token != NULL) {
 
    printf("%d %s\n",i++,token);

		token = strtok(NULL," ");
   
     }
	}
}