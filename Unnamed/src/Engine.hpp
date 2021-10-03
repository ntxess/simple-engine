#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window/ContextSettings.hpp>

#include "FPS.hpp"
#include "InputHandler.hpp"

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
    InputHandler _inputHandler;
    GameState _state;
    GameActor _actor;
    unsigned int _width;
    unsigned int _height;
    
    Engine(unsigned int width, unsigned int height);
    ~Engine();
    void Init();
    void Run();
    void ProcessInput();
    void Update();
    void Render(float interpolation);
    void Clear();
    bool isOpen() const;
};