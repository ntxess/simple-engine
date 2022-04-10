#include "ResourceMonitor.hpp"

ResourceMonitor::ResourceMonitor() : _fps(0)
{
    if (!_font.loadFromFile("resources/font/VCR_OSD_MONO_1.001.ttf"))
    {
        std::cout << "FAILURE TO LOAD FONT TYPE!" << std::endl;
        exit(-1);
    }
    _text.setFont(_font);
    _text.setCharacterSize(20);
    _text.setFillColor(sf::Color::White);
    _text.setPosition(sf::Vector2f(0, 0));
}

ResourceMonitor::~ResourceMonitor()
{}

std::string ResourceMonitor::FloatToString(float d)
{
    std::stringstream ss;
    ss << d;
    return ss.str();
}

void ResourceMonitor::Reposition(sf::Vector2f pos)
{
    _text.setPosition(pos);
}

void ResourceMonitor::Update()
{
    if (_clock.getElapsedTime().asSeconds() >= 1.f)
    {
        _text.setString("FPS: " + FloatToString(_fps) + "\n" + FloatToString(1000 / _fps) + "m/s");
        _fps = 0;
        _clock.restart();
    }
    ++_fps;
}

void ResourceMonitor::Render(const std::unique_ptr<sf::RenderWindow>& rw)
{
    rw->draw(_text);
}