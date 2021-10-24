#include "MainMenu.hpp"

MainMenu::MainMenu(std::shared_ptr<GameData>& data) 
    : _data(data) 
{}

MainMenu::~MainMenu()
{}

void MainMenu::Init()
{
	GameObjectRef background = std::make_unique<GameObject>(
		nullptr,
		nullptr,
		std::make_unique<Background>()
		);

    _assets.push_back(std::move(background));
}

void MainMenu::ProcessInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        _data->_machine->AddState(std::make_unique<DebugScene>(_data), false);
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
    _fps.Update();
    _fps.Render(rw);
}

void MainMenu::Pause()
{

}

void MainMenu::Resume()
{

}