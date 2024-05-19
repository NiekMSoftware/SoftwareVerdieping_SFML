#include "Engine/lib/Application.h"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        Application app;
        app.Run();
    }
    catch(std::exception& exception)
    {
        std::cout << "Failed to run app: " << exception.what();
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
