#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include "InputHandler.hpp"
#include "GameObject.hpp"
#include "FPSTracker.hpp"
#include "PlayerInput.hpp"
#include "CPUInput.hpp"
#include "Sprite.hpp"
#include "MusicNote.hpp"

enum class GameState
{
    GAME_ACTIVE,
    GAME_MENU
};

const double MS_PER_UPDATE = 1.0 / 60.0;

class Engine
{
public:
    sf::RenderWindow* _mainContext;
    GameState _state;
    unsigned int _width;
    unsigned int _height;

    InputHandler _inputHandler;

    GameObject* _currentFocus;

    std::vector<GameObject*> _entityAll;
    std::vector<GameObject*> _entityLive;

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