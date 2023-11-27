#pragma once

#include <SFML/Graphics.hpp>

#include "EntityManager.h"
#include "Scene.h"
#include "Asset.h"
#include "Serializer.h"

#include <imgui.h>
#include <imgui-SFML.h>
#include <imgui_stdlib.h>
#include <ImGuiFileDialog.h>



typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

class GameEngine
{
private:

	friend class Serializer;

	SceneMap m_SceneMap;
	Asset m_Asset;
	sf::RenderWindow m_Window;
	std::string m_CurrentScene;
	bool m_Running = true;
	size_t m_SimulatedFrame = 0;

	EntityManager m_EditorEntityManager;
	std::shared_ptr<Entity> m_SelectedEntity;
	std::shared_ptr<Entity> m_PreviousSelectedEntity = nullptr;
	
	void init(const std::string& Path);
	void update();
	void sUserInput();
	std::shared_ptr<Entity> m_TransformGizmoX;
	std::shared_ptr<Entity> m_TransformGizmoY;

public:

	float m_ViewPortHeight;
	float m_ViewPortWidth;

	std::shared_ptr<Scene> CurrentScene();
	Serializer m_Serializer;
	double m_DeltaTime;
	std::string m_CurrentMode = "EditorMode";
	static std::string m_Button;
	static bool canValidateDialog;
	bool m_EditorMode = true;
	sf::RenderWindow m_RenderWindow;
	sf::Clock m_DeltaClock;
	sf::Event m_Event;

	bool m_MoveMode = false;
	static std::string m_TransformStatus;
	static std::string m_ImagePath;
	static bool m_ShowContentDrawer;
	static std::string m_TextureName;
	static float m_GlobalZoom;

	Vec2 m_MousePos;

	explicit GameEngine(const std::string& path);
	~GameEngine();

	void ShowGizmo(Vec2 gPos);
	inline void InfosPane(const char* vFilter, IGFDUserDatas vUserDatas, bool* vCantContinue);
	void MouseInteract();
	void GizmoAction();

	const std::string GetCurrentSceneName() const;
	void RenderImGui();
	void ChangeScene(const std::string& SceneName, std::shared_ptr<Scene> Scene, bool EndCurrentScene = false);

	const void SelectEntity(std::shared_ptr<Entity>& e);


	void run();
	void quit();
	void debug();

	sf::RenderWindow& Window();
	Asset& GetAssets();
	bool IsRunning();
};

