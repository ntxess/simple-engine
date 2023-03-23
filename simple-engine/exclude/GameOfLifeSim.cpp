#include "GameOfLifeSim.hpp"

GameOfLifeSim::GameOfLifeSim(std::shared_ptr<GameData>& data)
	: _data(data)
{}

GameOfLifeSim::~GameOfLifeSim()
{}

void GameOfLifeSim::Init()
{
	std::cout << "<<Game of Life>>" << std::endl;

	float width = float(_data->window->getSize().x);
	float height = float(_data->window->getSize().y);
	_data->_defaultView.setSize(width, height);
	_data->_focusedView.setSize(width, height);
	_data->_defaultView.setCenter(width / 2, height / 2);
	_data->window->setView(_data->_defaultView);

	gridWorld = std::vector<std::vector<int>>(width, std::vector<int>(height, 0));
	buffer = std::vector<std::vector<int>>(gridWorld.size(), std::vector<int>(gridWorld[0].size(), 0));
	for (auto& row : gridWorld) {
		std::generate(row.begin(), row.end(), []() {
			return rand() % 10 == 0 ? 1 : 0;
			});
	}

	windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoMove;
	windowFlags |= ImGuiWindowFlags_NoResize;
	windowFlags |= ImGuiWindowFlags_NoTitleBar;
	windowFlags |= ImGuiWindowFlags_NoBackground;

	ImGui::SFML::Init(*_data->window);
}

void GameOfLifeSim::ProcessEvent(const sf::Event& event)
{
	if (drawMode)
	{
		if (event.type == sf::Event::MouseButtonPressed)
			mouseHold = true;

		if (drawMode && event.type == sf::Event::MouseButtonReleased)
			mouseHold = false;
	}

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
			_data->sceneManager->AddScene(std::make_unique<MainMenu>(_data), true);
	}
}

void GameOfLifeSim::ProcessInput()
{}

void GameOfLifeSim::Update(const float& deltaTime)
{}

void GameOfLifeSim::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
	DrawOptions(rw, deltaTime);

	if (drawMode)
	{
		if (mouseHold)
		{
			int posX = sf::Mouse::getPosition(*_data->window).x;
			int posY = sf::Mouse::getPosition(*_data->window).y;
			gridWorld[posX][posY] = 1;
		}
	}
	else 
	{
		for (int i = 0; i < gridWorld.size(); i++) {
			for (int j = 0; j < gridWorld[i].size(); j++) {
				int neighbors = GetNeighbors(gridWorld, i, j);
				if (gridWorld[i][j] && neighbors < 2)
					buffer[i][j] = 0;
				else if (gridWorld[i][j] && (neighbors == 2 || neighbors == 3))
					buffer[i][j] = gridWorld[i][j];
				else if (gridWorld[i][j] && neighbors > 3)
					buffer[i][j] = 0;
				else if (!gridWorld[i][j] && neighbors == 3)
					buffer[i][j] = 1;
			}
		}
		gridWorld = buffer;
	}


	for (int i = 0; i < gridWorld.size(); i++) {
		for (int j = 0; j < gridWorld[i].size(); j++) {
			if (gridWorld[i][j]) {
				sf::RectangleShape rectangle;
				rectangle.setSize(sf::Vector2f(1, 1));
				rectangle.setFillColor(sf::Color(50, 168, 82));
				rectangle.setPosition(i, j);
				rw->draw(rectangle);
			}
		}
	}
}

void GameOfLifeSim::Pause()
{}

void GameOfLifeSim::Resume()
{}

entt::registry& GameOfLifeSim::GetRegistry()
{
	return _registry;
}

void GameOfLifeSim::DrawOptions(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime)
{
	ImGui::SFML::Update(*_data->window, sf::seconds(deltaTime));
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize({ 10, 50 });
	ImGui::Begin("Demo", NULL, windowFlags);

	if (ImGui::Button("Max"))
	{
		gridWorld = std::vector<std::vector<int>>(gridWorld.size(), std::vector<int>(gridWorld[0].size(), 0));
		buffer = std::vector<std::vector<int>>(gridWorld.size(), std::vector<int>(gridWorld[0].size(), 0));
		ReadFile("resources/gameOfLifePatterns/max.txt");
	}

	if (ImGui::Button("Half Max"))
	{
		gridWorld = std::vector<std::vector<int>>(gridWorld.size(), std::vector<int>(gridWorld[0].size(), 0));
		buffer = std::vector<std::vector<int>>(gridWorld.size(), std::vector<int>(gridWorld[0].size(), 0));
		ReadFile("resources/gameOfLifePatterns/halfmax.txt");
	}

	if (ImGui::Button("Space Filler 1"))
	{
		gridWorld = std::vector<std::vector<int>>(gridWorld.size(), std::vector<int>(gridWorld[0].size(), 0));
		buffer = std::vector<std::vector<int>>(gridWorld.size(), std::vector<int>(gridWorld[0].size(), 0));
		ReadFile("resources/gameOfLifePatterns/spacefill1.txt");
	}

	if (ImGui::Button("Space Filler 2"))
	{
		gridWorld = std::vector<std::vector<int>>(gridWorld.size(), std::vector<int>(gridWorld[0].size(), 0));
		buffer = std::vector<std::vector<int>>(gridWorld.size(), std::vector<int>(gridWorld[0].size(), 0));
		ReadFile("resources/gameOfLifePatterns/spacefill2.txt");
	}

	if (ImGui::Button("Random"))
	{
		gridWorld = std::vector<std::vector<int>>(_data->window->getSize().x, std::vector<int>(_data->window->getSize().y, 0));
		buffer = std::vector<std::vector<int>>(gridWorld.size(), std::vector<int>(gridWorld[0].size(), 0));
		for (auto& row : gridWorld) {
			std::generate(row.begin(), row.end(), []() {
				return rand() % 10 == 0 ? 1 : 0;
				});
		}
	}

	if (ImGui::Button("Draw Mode"))
	{
		drawMode = true;
	}
	ImGui::SameLine();
	if (ImGui::Button("Apply"))
	{
		drawMode = false;
	}

	ImGui::End();
	ImGui::SFML::Render(*_data->window);
}

int GameOfLifeSim::GetNeighbors(std::vector<std::vector<int>>& board, int i, int j) {
	int neighbors = 0;

	// top row
	if (i - 1 >= 0 && j - 1 >= 0 && board[i - 1][j - 1])
		neighbors++;

	if (i - 1 >= 0 && board[i - 1][j])
		neighbors++;

	if (i - 1 >= 0 && j + 1 < board[i - 1].size() && board[i - 1][j + 1])
		neighbors++;

	// mid row
	if (j - 1 >= 0 && board[i][j - 1])
		neighbors++;

	if (j + 1 < board[i].size() && board[i][j + 1])
		neighbors++;

	// bot row
	if (i + 1 < board.size() && j - 1 >= 0 && board[i + 1][j - 1])
		neighbors++;

	if (i + 1 < board.size() && board[i + 1][j])
		neighbors++;

	if (i + 1 < board.size() && j + 1 < board[i + 1].size() && board[i + 1][j + 1])
		neighbors++;

	return neighbors;
} 

void GameOfLifeSim::ReadFile(const std::string& filename)
{
	std::ifstream input(filename);
	if (!input.is_open())
	{
		std::cout << "Failed to open: " << filename << "\n";
	}
	else
	{
		int w_midWidth = _data->window->getSize().x / 2;
		int w_midHeight = _data->window->getSize().y / 2;
		int midWidth = 0;
		int midheight = 0;

		std::string line;
		input >> line;
		midWidth = stoi(line) / 2;
		input >> line;
		midheight = stoi(line);

		std::string pattern;
		int j = w_midHeight - midheight;
		while (input >> line) {
			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] == 'O')
				{
					gridWorld[i + (w_midWidth - midWidth)][j] = 1;
				}
			}
			j++;
			pattern += line;
		}
	}
}