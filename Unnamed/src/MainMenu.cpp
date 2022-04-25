#include "MainMenu.hpp"

MainMenu::MainMenu(std::shared_ptr<GameData>& data)
    : _data(data) 
{}

MainMenu::~MainMenu()
{}

void MainMenu::Init()
{
    //_background  = std::make_unique<UIObject>(_data->_holder, "Background");
    //_startButton = std::make_unique<UIObject>(_data->_holder, "StartButton");
    //_quitButton  = std::make_unique<UIObject>(_data->_holder, "QuitButton");

    //_startButton->GetSprite().setPosition(sf::Vector2f(160, 500));
    //_quitButton->GetSprite().setPosition(sf::Vector2f(160, 800));

    //_assets.push_back(std::move(_background));
    //_assets.push_back(std::move(_startButton));
    //_assets.push_back(std::move(_quitButton));

}

void MainMenu::ProcessEvent(const sf::Event& event)
{}

void MainMenu::ProcessInput(const sf::Event& event)
{
    //sf::Vector2f mousePos = _data->_window->mapPixelToCoords(sf::Mouse::getPosition(*_data->_window));
    //if (_startButton->GetSprite().getGlobalBounds().contains(mousePos))
    //{
    //    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    //    {
    //        _data->_machine->AddState(std::make_unique<DebugScene>(_data));
    //    }
    //}

    //if (_quitButton->GetSprite().getGlobalBounds().contains(mousePos))
    //{
    //    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    //    {
    //        _data->_window->close();
    //    }
    //}
}

void MainMenu::Update(const float& deltaTime)
{
    //for (int i = 0; i < _assets.size(); i++)
    //{
    //    _assets[i]->Update(deltaTime);
    //}
}

void MainMenu::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
    //for (int i = 0; i < _assets.size(); i++)
    //{
    //    _assets[i]->Render(rw, deltaTime, interpolation);
    //}

    //_background->Render(rw, deltaTime, interpolation);
    //_startButton->Render(rw, deltaTime, interpolation);
    //_quitButton->Render(rw, deltaTime, interpolation);
    _fps.Update();
    _fps.Render(rw);
}

void MainMenu::Pause()
{}

void MainMenu::Resume()
{}

entt::registry& MainMenu::GetRegistry()
{
    return _registry;
}
