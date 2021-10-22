#include "SceneManager.hpp"

SceneManager::SceneManager() : 
	_currentScene(nullptr), 
	_nextScene(nullptr) {}

SceneManager::~SceneManager()
{
	delete _currentScene;
	delete _nextScene;
	for (auto scene : _sceneList) {
		delete scene;
	}
}

Scene* SceneManager::GetScene()
{
	return _currentScene;
}

Scene* SceneManager::GetNextScene()
{
	return _nextScene;
}

void SceneManager::LoadScene()
{
	_currentScene->Init();
}

void SceneManager::LoadNextScene()
{

}

void SceneManager::AddScene(Scene* newScene)
{
	_sceneList.push_back(newScene);
}

void SceneManager::SwitchScene()
{

}

void SceneManager::SwitchScene(Scene* scene)
{

}

void SceneManager::RemoveScene()
{
	// TODO
}
