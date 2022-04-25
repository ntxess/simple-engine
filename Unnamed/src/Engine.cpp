#include "Engine.hpp"

Engine::Engine(unsigned int width, unsigned int height, std::string title) 
    : _data(std::make_unique<GameData>())
    , _width(width)
    , _height(height)
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 4;
    settings.minorVersion = 3;

    _data->_window->create(sf::VideoMode(width, height), title, sf::Style::Default, settings);

    try
    {
        _data->_holder.acquire("Background", 
            thor::Resources::fromFile<sf::Texture>("resources/bg/bg1.png"), 
            thor::Resources::Reuse);
        _data->_holder.acquire("StartButton", 
            thor::Resources::fromFile<sf::Texture>("resources/bg/start.png"), 
            thor::Resources::Reuse);
        _data->_holder.acquire("QuitButton", 
            thor::Resources::fromFile<sf::Texture>("resources/bg/quit.png"), 
            thor::Resources::Reuse);
        _data->_holder.acquire("Triangle", 
            thor::Resources::fromFile<sf::Texture>("resources/player/triangle.png"), 
            thor::Resources::Reuse);
        _data->_holder.acquire("Ship", 
            thor::Resources::fromFile<sf::Texture>("resources/player/ship0.png"), 
            thor::Resources::Reuse);
        _data->_holder.acquire("Shot", 
            thor::Resources::fromFile<sf::Texture>("resources/player/shotParticle.png"), 
            thor::Resources::Reuse);
    }
    catch (thor::ResourceLoadingException& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    std::unique_ptr<MCircle> mCircle = std::make_unique<MCircle>();
    std::unique_ptr<MRandom> mRandom = std::make_unique<MRandom>();
    std::unique_ptr<MStraight> mStraight = std::make_unique<MStraight>();

    _data->_pathMap["mCircle"] = std::move(mCircle->head);
    _data->_pathMap["mRandom"] = std::move(mRandom->head);
    _data->_pathMap["mStraight"] = std::move(mStraight->head);
}

Engine::~Engine()
{}

void Engine::Run()
{
    //_data->_machine->AddState(std::make_unique<MainMenu>(_data));
    //_data->_machine->AddState(std::make_unique<DebugScene>(_data));
    _data->_machine->AddState(std::make_unique<Sandbox>(_data));

    float newTime, frameTime, interpolation;
    float currentTime = _clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    sf::Event event;
    while (_data->_window->isOpen())
    {
        newTime = _clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;

        _data->_machine->ProcessStateChange();

        while (_data->_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _data->_window->close();

            _data->_machine->GetActiveState()->ProcessEvent(event);
        }

        _data->_machine->GetActiveState()->ProcessInput(event);

        while (accumulator >= deltaTime)
        {
            _data->_machine->GetActiveState()->Update(deltaTime);
            accumulator -= deltaTime;
        }

        interpolation = accumulator / deltaTime;

        _data->_window->clear();
        _data->_animator.update(sf::seconds(deltaTime));
        _data->_machine->GetActiveState()->Render(_data->_window, deltaTime, interpolation);
        _data->_window->display();
    }
}





