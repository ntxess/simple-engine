#include "SceneManager.hpp"

SceneManager::SceneManager() 
	: m_isRemoving(false), m_isAdding(false), m_isReplacing(false)
{}

void SceneManager::AddScene(std::unique_ptr<Scene> newScene, bool isReplacing)
{
	m_isAdding = true;
	m_isReplacing = isReplacing;
	m_newScene = std::move(newScene);
}

void SceneManager::RemoveScene()
{
	m_isRemoving = true;
}

void SceneManager::ProcessSceneChange()
{
	if (m_isRemoving && !m_scenes.empty())
	{
		m_scenes.pop();
		if (!m_scenes.empty())
		{
			m_scenes.top()->Resume();
		}
		m_isRemoving = false;
	}

	if (m_isAdding)
	{
		if (!m_scenes.empty())
		{
			if (m_isReplacing)
			{
				m_scenes.pop();
			}
			else
			{
				m_scenes.top()->Pause();
			}
		}
		m_scenes.push(std::move(m_newScene));
		m_scenes.top()->Init();
		m_isAdding = false;
	}
}

std::unique_ptr<Scene>& SceneManager::GetActiveScene()
{
	return m_scenes.top();
}
