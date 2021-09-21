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

    //_mainContext->setFramerateLimit(60);
    std::cout << "Done." << std::endl;
}

void Engine::Run()
{
    std::cout << "Game Running..." << std::flush;

    Drawable* fps = new FPS();
    fps->Reposition(sf::Vector2f(300,512));
    _drawList.push_back(fps);
    
    float deltaTime = 0.0f;
    sf::Clock clock;

    while(isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        _mainContext->clear();
        ProcessInput(deltaTime);
        Update(deltaTime);
        Draw();
        _mainContext->display();
    }

    std::cout << "Done." << std::endl;
}

void Engine::ProcessInput(float deltaTime)
{

}

void Engine::Update(float deltaTime)
{

}

void Engine::Draw()
{
    for(auto obj : _drawList)
    {
        obj->Draw(_mainContext);
    }
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

