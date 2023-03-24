#pragma once
#include "GameData.hpp"
#include "Scenes/EmptyScene.hpp"

class Engine
{
private:
    const float m_deltaTime = 1.0f / 165.0f;
    const float m_aspectRatio;
    std::shared_ptr<GameData> m_data;
    sf::Clock m_clock;

public:
    Engine() = default;
    Engine(unsigned int width, unsigned int height, std::string title);
    ~Engine() = default;

    void Run();
    void GameThread();
};
