#include <iostream>
#include <string>
void remove_space(std::string str)
{
	std::string word = "";
	for (auto x : str)
	{
		if (x == ' ')
		{
			std::cout << word << std::endl;
			word = "";
		}
		else
		{
			word = word + x;
		}
	}
	std::cout << word << std::endl;
}
int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		std::cout << "No program arguments found." << std::endl;
		return 1;
	}

	
	// Get the first argument
	int i = 1;
	std::string argumentAsString;
	std::string space = " ";
	while (argv[i] != 0)
	{
		argumentAsString += argv[i] + space;
		i++;
	}
	
	//std::cout << argumentAsString << std::endl;
	remove_space(argumentAsString);
}