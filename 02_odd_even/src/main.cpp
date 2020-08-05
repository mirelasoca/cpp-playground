#include <stdio.h>

#include <iostream>
#include <string>

void printOddOrEven(int number)
{
	if (number % 2 == 0)
	{
		printf("EVEN\n");
	}
	else
	{
		printf("ODD\n");
	}
}

int main(int argc, char* argv[])
{
	int number = -13;

	// What is this program expected to do?
	// - Shows whether an argument is an ODD or EVEN number.
	// How to launch it?
	// - Execute the binary and pass a parameter to it?
	// - E.g. Open CMD in bin/Debug or bin/Release
	//		  02_odd_even.exe 1		=> Output: ODD
	//		  02_odd_even.exe 2		=> Output: EVEN
	//		  02_odd_even.exe 		=> Output: No program arguments found.
	//		  02_odd_even.exe ABC   => Undefined output (do whatever).
	//		

	// Make sure there are some program arguments available.
	if (argc <= 1)
	{
		printf("No program arguments found.\n");
	}

	// TODO(Gusti): i don't know why this doesn't work, but someone please FIX it.
	// --------------- start
	else
	{
		// Get the first argument
		std::string argumentAsString = argv[1];
		const char* argumentAsCharArray = argumentAsString.c_str();
		bool is_string = false;

		//number = argv[1]; // No
		//should use atoi?
		// or std::stoi?
		if (argumentAsCharArray[0] == '-')
		{
			for (int i = 1; i < strlen(argumentAsCharArray); i++)
			{
				if (isdigit(argumentAsCharArray[i]) == 0)
				{
					is_string = true;
				}
			}
		}
		else
		{
			for (int i = 0; i < strlen(argumentAsCharArray); i++)
			{
				if (isdigit(argumentAsCharArray[i]) == 0)
				{
					is_string = true;
				}
			}
		}

		if (is_string)
		{
			printf("NAN");
		}
		else
		{
			number = atoi(argumentAsCharArray);
			printOddOrEven(number);
		}
		//std::cout << argumentAsString << std::endl; // i think this should be removed

		// --------------- stop

		

	}
	
	return 0;
}