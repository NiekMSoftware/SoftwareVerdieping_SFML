#include <iostream>
#include "Application.hpp"


int main()
{
	try
	{
		Application app;
		app.Run();
	}
	catch (std::bad_exception& e)
	{
		std::cout << "Womp womp" << e.what();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
