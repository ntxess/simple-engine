#include <iostream>
#include "Engine.hpp"

int main() 
{
    std::cout << "Ver 1.0" << std::endl;
    Engine engine(960, 640);
    engine.Init();
    engine.Run();
    std::cout << "Destroying World" << std::endl;
    system("pause");
    return 0;
}

