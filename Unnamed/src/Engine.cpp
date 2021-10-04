#include "Engine.hpp"

Engine::Engine(unsigned int width, unsigned int height) 
    : _state(GAME_ACTIVE), _width(width), _height(height), _mainActor(new GameActor()) {}

Engine::~Engine()
{
    delete _mainContext;
    delete _command;
    delete _mainActor;
    for (int i = 0; i < _entityList.size(); i++)
    {
        delete _entityList[i];
    }
    _entityList.clear();
}

void Engine::Init()
{   
    std::cout << "Starting Initialization..." << std::flush;

    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 4;
    settings.minorVersion = 3;

    _mainContext = new sf::RenderWindow
        (sf::VideoMode(_width, _height), "Unnamed", sf::Style::Default, settings);

    std::cout << "Done." << std::endl;
    std::cout << "Opengl Ver " << settings.majorVersion << "." << settings.minorVersion << std::endl;

    _entityList.push_back(new FPS());
    _entityList.push_back(_mainActor);
}

void Engine::Run()
{
    std::cout << "Game Running..." << std::flush;

    sf::Clock clock;
    double accumulator = 0.0f;

    while(isOpen())
    {
        accumulator += clock.restart().asSeconds();
        Clear();
        ProcessInput();
        while (accumulator >= MS_PER_UPDATE)
        {
            Update();
            accumulator -= MS_PER_UPDATE;
        }
        Render(accumulator / MS_PER_UPDATE);
    }

    std::cout << "Done." << std::endl;
}

void Engine::ProcessInput()
{
    _command = _inputHandler.HandleInput();
    if (_command) _command->execute(*_mainActor);
}

void Engine::Update()
{
    // Remember we are updating physics and AI based of a fixed time step
    // Therefore we do not need to pass in delta time
    for (int i = 0; i < _entityList.size(); i++)
    {
        _entityList[i]->Update();
    }
}

void Engine::Render(double interpolation)
{
    for (int i = 0; i < _entityList.size(); i++)
    {
        _entityList[i]->Render(_mainContext, interpolation);
    }
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

sf::RenderTarget* Engine::GetContext()
{
    return _mainContext;
}

