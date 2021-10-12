#include "Engine.hpp"

Engine::Engine(unsigned int width, unsigned int height) : 
    _mainContext(nullptr),
    _state(GameState::GAME_ACTIVE),
    _width(width), 
    _height(height),
    _currentFocus(nullptr) {}

Engine::~Engine()
{
    delete _mainContext;
    delete _currentFocus;
    for (int i = 0; i < _entityAll.size(); i++)
    {
        delete _entityAll[i];
    }
    _entityAll.clear();
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

    //_entityAll.push_back(_mainActor);
    //_currentFocus = new GameObject(new PlayerInputComponent(), nullptr, nullptr);
    _currentFocus = new GameObject();
}

void Engine::Run()
{
    std::cout << "Game Running..." << std::flush;

    FPSTracker fps;
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
        fps.Update();
        fps.Render(_mainContext);
        Render(accumulator / MS_PER_UPDATE);
    }

    std::cout << "Done." << std::endl;
}

void Engine::ProcessInput()
{
    if(_currentFocus->Input())
        _inputHandler.HandleInput(*_currentFocus);
}


void Engine::Update()
{
    for (int i = 0; i < _entityAll.size(); i++)
    {
        _entityAll[i]->Update();
    }
}

void Engine::Render(double interpolation)
{
    for (int i = 0; i < _entityAll.size(); i++)
    {
        _entityAll[i]->Render(_mainContext, interpolation);
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

