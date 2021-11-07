#include "DebugScene.hpp"

DebugScene::DebugScene(std::shared_ptr<GameData> &data) 
    :_data(data) 
{}

DebugScene::~DebugScene()
{}

void DebugScene::Init()
{
    sf::Texture& texure = _data->_holder["Ship1"];
    _ship.setTexture(texure);
    _ship.setScale(sf::Vector2f(3,3));
    _ship.setPosition(sf::Vector2f(800, 800));
    thor::FrameAnimation flying;
    for (int i = 0; i < 4; i++)
    {
        flying.addFrame(1.f, sf::IntRect(16 * i, 0, 16, 24));
    }

    _animator.addAnimation("flying", flying, sf::seconds(2.f));

    _currentFocus = std::make_unique<GameObject>(
        std::make_unique<PlayerInput>(), 
        nullptr, 
        std::make_unique<Sprite>(_data->_holder, "Ship")
        );
    _currentFocus->_velocity = 720;
    _currentFocus->GetGraphics()->SetScale(sf::Vector2f(3,3));

    //thor::FrameAnimation flying;
    //flying.addFrame(1.f, sf::IntRect(0, 0, 20, 20));
    //flying(_currentFocus->GetGraphics()->GetSprite(), 0.f);
    //_currentFocus->GetGraphics()->GetAnimator()->addAnimation("flying", flying, sf::seconds(1.f));

    GameObjectRef background = std::make_unique<GameObject>(std::make_unique<Sprite>(_data->_holder, "Background"));

    _currentFocus->GetGraphics()->SetPosition(sf::Vector2f(400, 300));
    _assets.push_back(std::move(background));
}

void DebugScene::ProcessInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        _data->_machine->AddState(std::make_unique<MainMenu>(_data));
    }

    _inputHandler.HandleInput(*_currentFocus);
}

void DebugScene::Update(float deltaTime)
{
    _currentFocus->Update(deltaTime);
    for (int i = 0; i < _assets.size(); i++)
    {
        _assets[i]->Update(deltaTime);
    }
    
    if (!_animator.isPlayingAnimation())
        _animator.playAnimation("flying");
    
    _animator.update(sf::seconds(deltaTime));
    _animator.animate(_ship);
}

void DebugScene::Render(RenderWindowRef& rw, float interpolation)
{
    for (int i = 0; i < _assets.size(); i++)
    {
        _assets[i]->Render(rw, interpolation);
    }
    _currentFocus->Render(rw, interpolation);
    _fps.Update();
    _fps.Render(rw);
    _data->_window->draw(_ship);
}

void DebugScene::Pause()
{
}

void DebugScene::Resume()
{
}
