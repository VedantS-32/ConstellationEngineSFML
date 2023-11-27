#include "SceneMenu.h"
#include "ScenePlay.h"
#include "Asset.h"
#include "GameEngine.h"
#include "Component.h"
#include "Action.h"

void SceneMenu::init()
{
	RegisterAction(sf::Keyboard::W, "Up");
	RegisterAction(sf::Keyboard::S, "Down");
	RegisterAction(sf::Keyboard::E, "Play");
	RegisterAction(sf::Keyboard::Escape, "Quit");

	m_Tittle = "Menu";
	m_MenuString.push_back("Option0");
	m_MenuString.push_back("Option1");
	m_MenuString.push_back("Option2");

	m_LevelPath.push_back("res/Level0.txt");
	m_LevelPath.push_back("res/Level0.txt");
	m_LevelPath.push_back("res/Level0.txt");

	m_MenuText.setFont(m_Game->GetAssets().GetFont("SomeTimeLater"));
	m_MenuText.setCharacterSize(64);
}

void SceneMenu::update()
{
	m_EntityManager.Update();
	sRender();
}

void SceneMenu::OnEnd()
{
    m_Game->quit();
}

void SceneMenu::sDoAction(const Action& action)
{
    if (action.Type() == "Start")
    {
        if (action.Name() == "Up")
        {
            if (m_SelectedMenuIndex > 0) { m_SelectedMenuIndex--; }
            else { m_SelectedMenuIndex = m_MenuString.size() - 1; }
        }
        else if (action.Name() == "Down")
        {
            m_SelectedMenuIndex = (m_SelectedMenuIndex + 1) % m_MenuString.size();
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

SceneMenu::SceneMenu(GameEngine* GEngine) : Scene(GEngine)
{
	init();
}

void SceneMenu::sRender()
{
    m_Game->Window().clear(sf::Color(100, 100, 255));
    auto StartHeight = 104;
    for (auto Menu : m_MenuString)
    {
        m_MenuText.setString(Menu);
        m_MenuText.setPosition(103, Height() - StartHeight);
        StartHeight += 120;
        m_Game->Window().draw(m_MenuText);
    }
}
