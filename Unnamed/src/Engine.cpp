#include "Engine.hpp"

Engine::Engine(unsigned int width, unsigned int height, std::string title) : _width(width), _height(height)
{
    std::cout << "Starting Initialization..." << std::flush;

    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 4;
    settings.minorVersion = 3;

    _data->window.create(sf::VideoMode(width, height), title, sf::Style::Default, settings);

    std::cout << "Done." << std::endl;
    std::cout << "Opengl Ver " << settings.majorVersion << "." << settings.minorVersion << "\n" << std::endl;

    _data->machine.AddState(std::make_unique<DebugScene>());
    Run();
}

Engine::~Engine()
{}

void Engine::Run()
{
    float newTime, frameTime, interpolation;
    float currentTime = _clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;
    while(IsOpen())
    {
        _data->machine.ProcessStateChange();

        newTime = _clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;

        _data->window.clear();
        _data->machine.GetActiveState()->ProcessInput();

        while (accumulator >= dt)
        {
            _data->machine.GetActiveState()->Update(dt);
            accumulator -= dt;
        }

        interpolation = accumulator / dt;
        _data->machine.GetActiveState()->Render(_data->window, interpolation);
        _data->window.display();
    }
}

bool Engine::IsOpen() const
{
    sf::Event event;
    _data->window.pollEvent(event);
    if (event.type == sf::Event::Closed)
    {
        _data->window.close();
        return false;
    }
    return true;
}




