#pragma once
#include <SFML/Graphics.hpp>

class Drawable
{
public:
    virtual void Reposition(sf::Vector2f pos) = 0;
    virtual void Draw(sf::RenderTarget* rt) = 0;
};