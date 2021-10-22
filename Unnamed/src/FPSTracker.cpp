#include "FPSTracker.hpp"

FPSTracker::FPSTracker() : _fps(0)
{
    if (!_font.loadFromFile("resources/font/VCR_OSD_MONO_1.001.ttf"))
    {
        std::cout << "FAILURE TO LOAD FONT TYPE!" << std::endl;
        exit(-1);
    }
    _text.setFont(_font);
    _text.setCharacterSize(20);
    _text.setFillColor(sf::Color::White);
    Reposition(sf::Vector2f(0, 0));
}

FPSTracker::~FPSTracker() 
{}

std::string FPSTracker::FloatToString(double d)
{
    std::stringstream ss;
    ss << d;
    return ss.str();
}

void FPSTracker::Reposition(sf::Vector2f pos)
{
    _text.setPosition(pos);
    _position = pos;
}

void FPSTracker::Update()
{
    if (_clock.getElapsedTime().asSeconds() >= 1.f)
    {
        _text.setString("FPS: " + FloatToString(_fps) + "\n" + FloatToString(1000 / _fps) + "m/s");
        _fps = 0;
        _clock.restart();
    }
    ++_fps;
}

void FPSTracker::Render(sf::RenderWindow* rt)
{
    rt->draw(_text);
}