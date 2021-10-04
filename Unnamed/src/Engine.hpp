#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window/ContextSettings.hpp>

#include "FPS.hpp"
#include "InputHandler.hpp"
#include "Entity.hpp"
#include "GameActor.hpp"

enum GameState
{
    GAME_ACTIVE,
    GAME_MENU
};

const double MS_PER_UPDATE = 1.0 / 165.0;

class Engine
{
public:
    sf::RenderWindow* _mainContext;
    GameState _state;
    unsigned int _width;
    unsigned int _height;

    InputHandler _inputHandler;
    Command* _command;

    Entity* _mainActor;
    std::vector<Entity*> _entityList;
    
    Engine(unsigned int width, unsigned int height);
    ~Engine();
    void Init();
    void Run();
    void ProcessInput();
    void Update();
    void Render(double interpolation);
    void Clear();
    bool isOpen() const;
    sf::RenderTarget* GetContext();
};