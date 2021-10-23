#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "DebugScene.hpp"

struct GameData
{
    StateMachine machine;
    sf::RenderWindow window;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Engine
{
private:
    const float dt = 1.0 / 120.0f;

public:
    GameDataRef _data = std::make_shared<GameData>();
    sf::Clock _clock;
    unsigned int _width;
    unsigned int _height;

    Engine(unsigned int width, unsigned int height, std::string title);
    ~Engine();
    void Run();
    bool IsOpen() const;
};