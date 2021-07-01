/**
 * Function prototype for the executeCommand function.
 * This function will handle parsing the command string.
 */

int executeCommand(char* str);
int externalCommand(char* commands[1024]);
void shellStart(char* str);
int allCommands(char* str);
int redirCheck(char* input, char* filename);

