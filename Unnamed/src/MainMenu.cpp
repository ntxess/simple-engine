#include "MainMenu.hpp"

MainMenu::MainMenu(std::shared_ptr<GameData>& data) : _data(data) 
{}

MainMenu::~MainMenu()
{}

void MainMenu::Init()
{
    ComponentRef background = std::make_unique<Component>(_data->_holder, "Background");
    _startButton = std::make_unique<Component>(_data->_holder, "StartButton");
    _quitButton = std::make_unique<Component>(_data->_holder, "QuitButton");

    _startButton->SetPosition(sf::Vector2f(160, 500));
    _quitButton->SetPosition(sf::Vector2f(160, 800));

    _assets.push_back(std::move(background));
}

void MainMenu::ProcessInput(sf::Event event)
{
    sf::Vector2f mousePos = _data->_window->mapPixelToCoords(sf::Mouse::getPosition(*_data->_window));
    if (_startButton->GetSprite().getGlobalBounds().contains(mousePos))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            _data->_machine->AddState(std::make_unique<DebugScene>(_data));
        }
    }

    if (_quitButton->GetSprite().getGlobalBounds().contains(mousePos))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            _data->_window->close();
        }
    }
}

void MainMenu::Update(float deltaTime)
{
    for (int i = 0; i < _assets.size(); i++)
    {
        _assets[i]->Update(deltaTime);
    }
}

void MainMenu::Render(RenderWindowRef& rw, float interpolation)
{
    for (int i = 0; i < _assets.size(); i++)
    {
        _assets[i]->Render(rw, interpolation);
    }
    _startButton->Render(rw, interpolation);
    _quitButton->Render(rw, interpolation);
    _fps.Update();
    _fps.Render(rw);
}

void MainMenu::Pause()
{

}

void MainMenu::Resume()
{

}