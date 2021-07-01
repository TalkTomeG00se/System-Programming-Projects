//Include definitions for C Runtime Library functions used in this program
#include <stdio.h>				//The standard I/O functions

//-------------------------------------------------------------------------------
//This is the main function, invoked by the C Runtime (CRT) to start the program
//-------------------------------------------------------------------------------
int main(void) {

	int upper = 0;	// Number of upper case letters
	int lower = 0;	// Number of lower case letters
	int vowel = 0;	// Number of vowels
	int consonant = 0;	// Number of constants
	int digits = 0;	// Number of digits
	int total = 0;	// Total number of characters in file

	int value;	// The value that will be read in from stdin
 
	while((value = getchar()) != EOF)	// Will go through whole file until EOF
	{
 

		if (value >= 'A' && value <= 'Z')  // Checks for upper case letters
		{
			upper++;

			if (value == 'A' || value == 'E' || value == 'I' || value == 'O' || value == 'U' || value == 'Y')  // Checks for upper case vowels
			{
				vowel++;

			}
			else {

				consonant++;

			}
		}

		else if (value >= 'a' && value <= 'z')  // Checks for lower case letters
		{
			lower++;

			if (value == 'a' || value == 'e' || value == 'i' || value == 'o' || value == 'u' || value == 'y')  // Checks for lower case vowels
			{
				vowel++;

			}
			else {

				consonant++;
			}



		}

		else if (value >= '0' && value <= '9')  // Checks for digits
		{
			digits++;

		}

		total++;  // Tracks total number of characters
   
	}

	printf("upper-case: %d", upper);
	printf("\nlower-case: %d", lower);
	printf("\nvowels: %d", vowel);
	printf("\nconsonants: %d", consonant);
	printf("\ndigits: %d", digits);
	printf("\ntotal: %d", total);
	printf("\n");

	return 0;

}
	
