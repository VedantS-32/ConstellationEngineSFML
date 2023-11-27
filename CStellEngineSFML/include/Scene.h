#pragma once
#include "GameEngine.h"
#include "EntityManager.h"
#include "Action.h"
#include "Asset.h"
#include "Physics.h"
#include "Component.h"
#include "Action.h"
#include "Asset.h"


typedef std::map<sf::Keyboard::Key, std::string> ActionMap;
typedef std::map<sf::Mouse::Button, std::string> ActionMapMouse;

class Physics;

class Scene
{
protected:
	friend class Serializer;
	friend class GameEngine;

	GameEngine* m_Game = nullptr;
	EntityManager m_EntityManager;
	ActionMap m_ActionMap;
	ActionMapMouse m_ActionMapMouse;
	Physics m_Physics;
	bool m_Pause = false;
	bool m_HasEnded = false;
	int m_CurrentFrame = 0;

	bool m_DrawTextures = true;
	bool m_DrawCollision = false;
	bool m_DrawGrid = false;
	const Vec2 m_GridSize = { 64, 64 };
	sf::Text m_GridText;

	Asset m_Asset;
	std::string m_ResourcePath;
	std::string m_EntityPath;

	sf::View m_View;

	virtual void OnEnd() = 0;
	void setPaused(bool Paused);

public:
	Scene();
	Scene(GameEngine* GEngine);
	Scene(GameEngine* GEngine, std::string ResourcePath, std::string EntityPath);

	std::shared_ptr<Entity> m_SelectedEntity = nullptr;
	std::shared_ptr<Entity> m_PreviousSelectedEntity = nullptr;
	std::shared_ptr<Entity> m_Player = nullptr;

	virtual void update() = 0;
	virtual void sDoAction(const Action& action) = 0;
	virtual void sRender() = 0;
	
	void DoAction(const Action& action);
	void Simulate(const size_t Frames);
	void RegisterAction(sf::Keyboard::Key InputKey, const std::string& ActionName);
	void RegisterAction(sf::Mouse::Button InputKey, const std::string& ActionName);

	void InitScene();
	void InitEditorKeyMap();
	void ProcessImGuiEvent();
	void SelectEntity();

	const std::shared_ptr<Entity> AddEntityAtInit(std::string Name);
	void AddEntityAtRuntime(std::string Name, Vec2 Position);
	void AddComponentAtRuntime(std::shared_ptr<Entity> e, std::string CName);

	void UpdateAttribute();

	void SaveScene();

	size_t Width() const;
	size_t Height() const;
	size_t CurrentFrame() const;


	// System
	void sSceneSystemUpdate();
	void sGravityUpdate();
	void sCollision();
	void sSceneSystemRender();
	void sSceneEditorAction(const Action& action);


	bool hasEnded() const;
	const ActionMap& GetActionMap() const;
	const ActionMapMouse& GetActionMapMouse() const;
	void DrawLine(const Vec2& p1, const Vec2& p2);
};
