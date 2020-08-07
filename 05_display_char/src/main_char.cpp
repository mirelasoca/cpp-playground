#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		std::cout << "No program arguments found." << std::endl;
		return 1;
	}

	
	// Get the first argument
	int i = 1;
	std::vector<std::string> argumentAsString;

	while (argv[i] != 0)
	{
		argumentAsString.emplace_back(argv[i]);
		i++;
	}
	
	for (std::string x : argumentAsString)
		std::cout << x << std::endl;
}