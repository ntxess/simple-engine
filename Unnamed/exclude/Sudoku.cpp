#include "Sudoku.hpp"

Sudoku::Sudoku(std::shared_ptr<GameData>& data)
	: _data(data)
{}

Sudoku::~Sudoku()
{

}

void Sudoku::Init()
{

}

void Sudoku::ProcessEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
			_data->sceneManager->AddScene(std::make_unique<MainMenu>(_data), true);
	}
}

void Sudoku::ProcessInput()
{

}

void Sudoku::Update(const float& deltaTime)
{

}

void Sudoku::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{

}

void Sudoku::Pause()
{

}

void Sudoku::Resume()
{

}

entt::registry& Sudoku::GetRegistry()
{
	return _registry;
}
