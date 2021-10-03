#include "Engine.hpp"

Engine::Engine(unsigned int width, unsigned int height) 
    : _state(GAME_ACTIVE), _width(width), _height(height) {}

Engine::~Engine()
{
    delete _mainContext;
}

void Engine::Init()
{   
    std::cout << "Starting Initialization..." << std::endl;

    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 3;
    settings.minorVersion = 1;

    _mainContext = new sf::RenderWindow
        (sf::VideoMode(_width, _height), "Unnamed", sf::Style::Default, settings);

    std::cout << "Done." << std::endl;
}

void Engine::Run()
{
    std::cout << "Game Running..." << std::flush;

    FPS fps;
    sf::Clock clock;
    double deltaTime = 0.0f;
    double lag = 0.0f;

    while(isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        lag += deltaTime;

        Clear();
        ProcessInput();
        while (lag >= MS_PER_UPDATE)
        {
            Update();
            fps.Update();
            lag -= MS_PER_UPDATE;
        }
        fps.Render(_mainContext);
        Render(lag / MS_PER_UPDATE);
    }

    std::cout << "Done." << std::endl;
}

void Engine::ProcessInput()
{
    Command* command = _inputHandler.HandleInput();
    if (command) command->execute(_actor);
}

void Engine::Update()
{

}

void Engine::Render(float interpolation)
{
    _mainContext->display();
}

void Engine::Clear()
{
    _mainContext->clear();
}

bool Engine::isOpen() const
{
    sf::Event event;
    _mainContext->pollEvent(event);
    if (event.type == sf::Event::Closed)
    {
        _mainContext->close();
        return false;
    }
    return true;
}

