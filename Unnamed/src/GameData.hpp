#pragma once
#include "SceneManager.hpp"
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
    thor::ResourceHolder<sf::Texture, std::string> textureManager;
    thor::ResourceHolder<sf::SoundBuffer, std::string> audioManager;
};