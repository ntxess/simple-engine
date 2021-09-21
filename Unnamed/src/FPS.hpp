#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

#include "Drawable.hpp"

class FPS : public Drawable
{
private:
    sf::Clock _clock;
    sf::Text  _text;
    sf::Font  _font;
    sf::Vector2f _position;
    double _fps;

    void Counter();
    std::string FloatToString(double d);

public:
    FPS();
    ~FPS();
    void Reposition(sf::Vector2f pos);
    void Draw(sf::RenderTarget* rt);
};