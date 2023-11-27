#include "Scene_GameMenu.h"
#include "ScenePlay.h"

Scene_GameMenu::Scene_GameMenu(GameEngine* GEngine, std::string ResourcePath, std::string EntityPath)
	: Scene(GEngine, ResourcePath, EntityPath)
{
	InitScene();
	InitSceneKeyMap();
	sSpawnPlayer();
}

Scene_GameMenu::~Scene_GameMenu()
{
}

void Scene_GameMenu::InitSceneKeyMap()
{
	RegisterAction(sf::Keyboard::W, "Up");
	RegisterAction(sf::Keyboard::S, "Down");
	RegisterAction(sf::Keyboard::E, "Play");
	RegisterAction(sf::Keyboard::Escape, "Quit");

}

void Scene_GameMenu::update()
{
	m_EntityManager.Update();
	if (!m_Game->m_EditorMode)
	{
		sMovement(1.0);
	}
	sLifespan();
	sAnimation();
	sRender();
	sSceneSystemUpdate();
}

void Scene_GameMenu::OnEnd()
{
	m_Game->quit();
}

void Scene_GameMenu::sSpawnPlayer()
{
}

void Scene_GameMenu::sAnimation()
{
}

void Scene_GameMenu::sMovement(float dt)
{
}

void Scene_GameMenu::sLifespan()
{
}

void Scene_GameMenu::sRender()
{
	if (!m_Pause) { m_Game->Window().clear(sf::Color(100, 100, 255)); }
	else { m_Game->Window().clear(sf::Color(50, 50, 150)); }
}

void Scene_GameMenu::sDoAction(const Action& action)
{
	if (action.Type() == "Start")
	{
		if (action.Name() == "Up")
		{
		}
		else if (action.Name() == "Down")
		{
		}
		else if (action.Name() == "Play")
		{
			m_Game->ChangeScene("Main", std::make_shared<ScenePlay>(m_Game, "res/Level1_Resource.yml", "res/Level1_Test.yml"));
		}
		else if (action.Name() == "Quit")
		{
			OnEnd();
		}
	}
}

void Scene_GameMenu::sDebug()
{
}

