#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window/ContextSettings.hpp>

#include "Drawable.hpp"
#include "FPS.hpp"

enum GameState
{
    GAME_ACTIVE,
    GAME_MENU
};

class Engine
{
public:
    sf::RenderWindow* _mainContext;
    std::vector<Drawable*> _drawList;
    GameState _state;
    unsigned int _width;
    unsigned int _height;
    
    Engine(unsigned int width, unsigned int height);
    ~Engine();
    void Init();
    void Run();
    void ProcessInput(float deltaTime);
    void Update(float deltaTime);
    void Draw();
    bool isOpen() const;
};