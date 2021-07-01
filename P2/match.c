/*----------------------------------------------------------------------------
**
** NAME
**   match -- print lines matching a pattern
**
** SYNOPSIS
**   match pattern
**
** DESCRIPTION
**   The match utility prints lines read from stdin matching a pattern.
**
**   The pattern must be a simple string (no regular expressions).
**
** EXAMPLES
**   match xyz     #Prints lines containing the string xyz read from stdin
**
** EXIT STATUS
**   0 One or more lines matched
**   1 No lines matched
**   2 An error occurred
**
** AUTHORS
**   01/17/19 Epoch.........................................................jrc
**
**---------------------------------------------------------------------------*/

//Import definitions required to access functionality implemented elsewhere
#include <stdio.h>    //Standard I/O functions and definitions
#include <stdlib.h>   //Standard library (includes exit function)
#include <string.h>  //String manipulation functions


//-----------------------------------------------------------------------------
//  usage -- Prints a usage message and exits with status=2
//-----------------------------------------------------------------------------
void usage(char* s) {
    
    //Print the usage message to stderr
    fprintf(stderr,"Usage:  %s pattern\n",s);
    
    //Force an exit.  This is equivalent to return 2 in main()
    exit(2);                //Exit status is 2
    
}


//-----------------------------------------------------------------------------
//  main -- The main function invoked by CRT to start the program
//-----------------------------------------------------------------------------
int main(int argc, char **argv) {

  //Initialize the normal (non-error) exit status
  int exitStatus = 1;            //No lines have matched (so far)

  //Verify the user remembered to include the pattern on the command line
  if (argc!=2) usage(argv[0]);   //Should have two entires, match & pattern

  //Get a pointer (reference) to the NUL-terminated pattern string
  char *pattern = argv[1];       //Pattern will get the add

  //Verify the pattern is not an empty string
  if (strlen(pattern)==0) usage(argv[0]);

    
  //<<<Insert your implementation for match here>>>

  char str[50];

  while (fgets(str, 50, stdin) != NULL) {

	  if (strstr(str, pattern) != NULL) {

		  fputs(str, stdout);
	  }
  }

    
  //Report the exit status to the CRT
  return exitStatus;
}


