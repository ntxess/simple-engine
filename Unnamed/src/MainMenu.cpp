#include "MainMenu.hpp"

MainMenu::MainMenu(std::shared_ptr<GameData>& data) 
    : _data(data) 
{}

MainMenu::~MainMenu()
{}

void MainMenu::Init()
{
	GameObjectRef background = std::make_unique<GameObject>(
		std::make_unique<Sprite>("resources/bg/bg1.png")
		);

    _startButton = std::make_unique<GameObject>(
        std::make_unique<Sprite>("resources/bg/start.png")
        );

    _quitButton = std::make_unique<GameObject>(
        std::make_unique<Sprite>("resources/bg/quit.png")
        );

    _startButton->GetGraphics()->SetPosition(sf::Vector2f(200, 400));
    _quitButton->GetGraphics()->SetPosition(sf::Vector2f(200, 800));

    _assets.push_back(std::move(background));
}

void MainMenu::ProcessInput()
{
    sf::Vector2f mousePos = _data->_window->mapPixelToCoords(sf::Mouse::getPosition(*_data->_window));
    if (_startButton->GetGraphics()->GetSprite().getGlobalBounds().contains(mousePos))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            _data->_machine->AddState(std::make_unique<DebugScene>(_data), false);
        }
    }

    if (_quitButton->GetGraphics()->GetSprite().getGlobalBounds().contains(mousePos))
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