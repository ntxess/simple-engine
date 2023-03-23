#pragma once
#include "Managers/SceneManager.hpp"
#include "Managers/AnimationManager.hpp"
#include "Managers/WaypointManager.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Thor/Resources.hpp"
#include <memory>

struct GameData
{
public:
    sf::RenderWindow window;
    sf::View defaultViewPort;
    SceneManager sceneManager;
    AnimationManager animationManager;
    WaypointManager waypointManager;
    thor::ResourceHolder<sf::Texture, std::string> textureManager;
    thor::ResourceHolder<sf::SoundBuffer, std::string> audioManager;
};