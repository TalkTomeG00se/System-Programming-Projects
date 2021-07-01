//-----------------------------------------------------------------------------
//
// NAME
//  sed253 -- Simplified editor
//
// SYNOPSIS
//  sed253
//  sed253 -s regex string
//  sed253 -d line1 line2
//
// DESCRIPTION
//  Simplified editor.  Copies lines read from stdin to stdout.  Options:
//
//  -s Substitute every occurrence of regex with string
//  -d Delete line1 through line2 inclusive
//
// ERRORS
//  Prints usage message and exits abnormally for invalid commands.  Prints an
//  error message and exits abnormally for other issues.
//
// LIMITATIONS
//  Lines of text are limited to a maximum of 1023 chars.
//
// AUTHORS
//  Epoch...................................................................jrc
//
//-----------------------------------------------------------------------------

//Bring in the definitions for our helper functions
#include "copy.h"
#include "substitute.h"
#include "delete.h"

//-----------------------------------------------------------------------------
// main -- the main function
//-----------------------------------------------------------------------------
int main(int argc, char **argv) {


  return 0;
}

