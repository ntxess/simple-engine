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
    std::cout << "Opengl Ver " << settings.majorVersion << "." << settings.minorVersion << "\n" << std::endl;

    _currentFocus = new GameObject(new PlayerInput(), nullptr, nullptr);
    GameObject* noteBlock = new GameObject(nullptr, nullptr, new MusicNote());
    noteBlock->Graphics()->SetPosition(sf::Vector2f(200, 20));
    _entityAll.push_back(noteBlock);
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
            Update(MS_PER_UPDATE);
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
    _inputHandler.HandleInput(*_currentFocus);
}

void Engine::Update(double deltaTime)
{
    for (int i = 0; i < _entityAll.size(); i++)
    {
        _entityAll[i]->Update(deltaTime);
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

