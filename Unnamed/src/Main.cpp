#include <iostream>
#include "Engine.hpp"

int main() 
{
    std::cout << "Ver 1.0" << std::endl;
    Engine engine(1920, 1080, "Unnamed");
    engine.Run();
    return 0;
}

