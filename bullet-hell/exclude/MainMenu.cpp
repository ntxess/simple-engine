#include "MainMenu.hpp"

MainMenu::MainMenu(std::shared_ptr<GameData>& data)
    : _data(data) 
{}

MainMenu::~MainMenu()
{}

void MainMenu::Init()
{
    std::cout << "<<Main Menu>>" << std::endl;

    float width = float(_data->window->getSize().x);
    float height = float(_data->window->getSize().y);
    _data->_defaultView.setSize(width, height);
    _data->_focusedView.setSize(width, height);
    _data->_defaultView.setCenter(width / 2, height / 2);
    _data->window->setView(_data->_defaultView);

    windowFlags = 0;
    windowFlags |= ImGuiWindowFlags_NoMove;
    windowFlags |= ImGuiWindowFlags_NoResize;
    windowFlags |= ImGuiWindowFlags_NoTitleBar;

    _performanceTracker = _registry.create();
    _registry.emplace<PerformanceMonitorComponent>(_performanceTracker);

    ImGui::SFML::Init(*_data->window);
}

void MainMenu::ProcessEvent(const sf::Event& event)
{
    ImGui::SFML::ProcessEvent(*_data->window, event);
}

void MainMenu::ProcessInput()
{}

void MainMenu::Update(const float& deltaTime)
{}

void MainMenu::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
    ImGui::SFML::Update(*_data->window, sf::seconds(deltaTime));

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(rw->getSize().x, rw->getSize().y));

    if (ImGui::Begin("MainMenu", NULL, windowFlags)) 
    {
        ImGui::SetWindowFontScale(10.f);
        ImGui::SetCursorPos(ImVec2(200, 100));
        ImGui::Text("Main Menu");

        ImGui::SetWindowFontScale(5.f);
        ImGui::SetCursorPos(ImVec2(200, 300));
        ImGui::Text("Select Game:");

        ImGui::SetCursorPos(ImVec2(250, 450));
        if (ImGui::Button("Game 1"))
        {
            _data->sceneManager->AddScene(std::make_unique<Sandbox>(_data), true);
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::SetWindowFontScale(2.5f);
            ImGui::SetCursorPos(ImVec2(1100, 400));
            ImGui::Text("Sandbox shoot-em-up\n\n"
                "Showcase features:\n"
                "\tQuadtree collision detection\n"
                "\tCPU player waypoint and tracking\n"
                "\tEntity component system\n"
            );
        }

        ImGui::SetWindowFontScale(5.f);
        ImGui::SetCursorPos(ImVec2(250, 550));
        if (ImGui::Button("Game 2"))
        {
            _data->sceneManager->AddScene(std::make_unique<PowerThrower>(_data), true);
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::SetWindowFontScale(2.5f);
            ImGui::SetCursorPos(ImVec2(1100, 400));
            ImGui::Text("Power Thrower! See how far you can throw!\n"
                "Beat Your Highscore in this arcade game.\n\n"
                "Showcase features:\n"
                "\tStats tracker\n"
                "\tInfinite world generation\n"
                "\tParallax Background\n"
                "\tSound effect system\n"
            );
        }

        ImGui::SetWindowFontScale(5.f);
        ImGui::SetCursorPos(ImVec2(250, 650));
        if (ImGui::Button("Game 3"))
        {
            _data->sceneManager->AddScene(std::make_unique<Sudoku>(_data), true);
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::SetWindowFontScale(2.5f);
            ImGui::SetCursorPos(ImVec2(1100, 400));
            ImGui::Text("Vertical scroller shoot-em-up\n\n"
                "Showcase features:\n"
                "\tQuadtree collision detection\n"
                "\tCPU player waypoint and tracking\n"
            );
        }

        ImGui::SetWindowFontScale(5.f);
        ImGui::SetCursorPos(ImVec2(250, 750));
        if (ImGui::Button("Game 4"))
        {
            _data->sceneManager->AddScene(std::make_unique<GameOfLifeSim>(_data), true);
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::SetWindowFontScale(2.5f);
            ImGui::SetCursorPos(ImVec2(1100, 400));
            ImGui::Text("Game of Life Simulation\n\n"
                "Showcase features:\n"
                "\tGrid-type\n"
            );
        }

        ImGui::SetWindowFontScale(5.f);
        ImGui::SetCursorPos(ImVec2(250, 850));
        if (ImGui::Button("Game 5"))
        {

        }
        if (ImGui::IsItemHovered())
        {
            ImGui::SetWindowFontScale(2.5f);
            ImGui::SetCursorPos(ImVec2(1100, 400));
            ImGui::Text("Vertical scroller shoot-em-up\n\n"
                "Showcase features:\n"
                "\tQuadtree collision detection\n"
                "\tCPU player waypoint and tracking\n"
            );
        }

        ImGui::SetWindowFontScale(5.f);
        ImGui::SetCursorPos(ImVec2(250, 950));
        if (ImGui::Button("Quit"))
        {
            exit(0);
        }
        //ImGui::SetWindowFontScale(5.f);
        //ImGui::SetCursorPos(ImVec2(1200, 300));
        //ImGui::Text("Description:");
    }

    ImGui::End();
    //ImGui::ShowDemoWindow();
    ImGui::SFML::Render(*_data->window);
    SystemHelper::PerformanceMetricUpdate(_registry, _performanceTracker, rw);
}

void MainMenu::Pause()
{}

void MainMenu::Resume()
{}

entt::registry& MainMenu::GetRegistry()
{
    return _registry;
}
