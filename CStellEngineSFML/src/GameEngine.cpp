#include "GameEngine.h"
#include "Asset.h"
#include "ScenePlay.h"
#include "Scene_GameMenu.h"
#include "SceneMenu.h"

#include "EntityManager.h"

#include <iostream>
#include <format>
#include <chrono>
#include <ctime>


std::string GameEngine::GameEngine::m_Button = "Play";
std::string GameEngine::GameEngine::m_TransformStatus = "Free";
std::string GameEngine::GameEngine::m_ImagePath = "";
bool GameEngine::GameEngine::canValidateDialog = false;
bool GameEngine::GameEngine::m_ShowContentDrawer = true;
std::string GameEngine::GameEngine::m_TextureName = "";
float GameEngine::GameEngine::m_GlobalZoom = 1.0f;


GameEngine::GameEngine(const std::string& Path)
{
	init(Path);
}

GameEngine::~GameEngine()
{
	ImGui::SFML::Shutdown();
}

void GameEngine::ShowGizmo(Vec2 gPos)
{
	if (CurrentScene()->m_SelectedEntity->GetComponent<CState>().selected)
	{
		auto& sGizmoXTransform = m_TransformGizmoX->GetComponent<CTransform>();
		auto& sGizmoXSprite = m_TransformGizmoX->GetComponent<CSprite>();
		sGizmoXTransform.pos = gPos;
		sGizmoXSprite.sprite.setRotation(sGizmoXTransform.angle);
		sGizmoXSprite.sprite.setPosition(sGizmoXTransform.pos.x, sGizmoXTransform.pos.y);
		sGizmoXSprite.sprite.setScale(sGizmoXTransform.scale.x, sGizmoXTransform.scale.y);

		//auto& sGizmoXBBox = m_TransformGizmoX->GetComponent<CBoundingBox>();
		//sf::RectangleShape rectX;
		//rectX.setSize(sf::Vector2f(sGizmoXBBox.size.x - 1, sGizmoXBBox.size.y - 1));
		//rectX.setOrigin(sf::Vector2f(0 , sGizmoXBBox.halfSize.y - 1));
		//rectX.setPosition(sGizmoXTransform.pos.x, sGizmoXTransform.pos.y);
		//rectX.setFillColor(sf::Color(0, 0, 0, 0));
		//rectX.setOutlineColor(sf::Color(255, 255, 255, 255));
		//rectX.setOutlineThickness(1);
		//m_Window.draw(rectX);


		m_Window.draw(sGizmoXSprite.sprite);

		auto& sGizmoYTransform = m_TransformGizmoY->GetComponent<CTransform>();
		auto& sGizmoYSprite = m_TransformGizmoY->GetComponent<CSprite>();
		sGizmoYTransform.pos = gPos;
		sGizmoYSprite.sprite.setRotation(sGizmoYTransform.angle);
		sGizmoYSprite.sprite.setPosition(sGizmoYTransform.pos.x, sGizmoYTransform.pos.y);
		sGizmoYSprite.sprite.setScale(sGizmoYTransform.scale.x, sGizmoYTransform.scale.y);

		//auto& sGizmoYBBox = m_TransformGizmoY->GetComponent<CBoundingBox>();
		//sf::RectangleShape rectY;
		//rectY.setSize(sf::Vector2f(sGizmoYBBox.size.x - 1, sGizmoYBBox.size.y - 1));
		//rectY.setOrigin(sf::Vector2f(sGizmoYBBox.halfSize.x - 1, sGizmoYBBox.size.y));
		//rectY.setPosition(sGizmoYTransform.pos.x, sGizmoYTransform.pos.y);
		//rectY.setFillColor(sf::Color(0, 0, 0, 0));
		//rectY.setOutlineColor(sf::Color(255, 255, 255, 255));
		//rectY.setOutlineThickness(1);
		//CurrentScene()->m_Physics.GetOverlappingEntity(m_TransformGizmoY, m_MousePos);
		//MouseInteract();
		//m_Window.draw(rectY);

		m_Window.draw(sGizmoYSprite.sprite);

		GizmoAction();
	}
}

void GameEngine::MouseInteract()
{
	//CurrentScene()->m_Physics.GetOverlappingEntity(m_TransformGizmoX, m_MousePos);
	//CurrentScene()->m_Physics.GetOverlappingEntity(m_TransformGizmoY, m_MousePos);

	SelectEntity(m_TransformGizmoX);
	SelectEntity(m_TransformGizmoY);

	GizmoAction();
}

void GameEngine::GizmoAction()
{
	if (m_TransformStatus == "Move" && CurrentScene()->m_SelectedEntity->GetComponent<CState>().selected)
	{
		CurrentScene()->m_SelectedEntity->GetComponent<CTransform>().pos = (Vec2(int(m_MousePos.x / 64), int(m_MousePos.y / 64)) * 64) + Vec2(32, 32);
	}
}

const std::string GameEngine::GetCurrentSceneName() const
{
	return m_CurrentScene;
}

void GameEngine::RenderImGui()
{
	auto& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 0.0f);

	ImGui::SFML::Update(m_Window, m_DeltaClock.restart());
	//sf::RenderTexture rt;
	//sf::Sprite sd;
	//rt.create(1280, 720);
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	ImGui::Begin(std::format("Viewport: {}", m_CurrentScene).c_str(), nullptr, io.ConfigFlags);
	ImGui::Text("Test");
	ImGui::InputFloat("Zoom", &m_GlobalZoom, 0.25f, 0.5f);
	//console_log(m_GlobalZoom);
	//sd.setTexture(t);
	//// Display the texture in an ImGui window
	//m_ViewPortHeight = ImGui::GetWindowHeight();
	//m_ViewPortWidth = ImGui::GetWindowWidth();

	ImGui::End();
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.11f, 0.15f, 0.17f, 0.75f));
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f, 0.15f, 0.17f, 0.75f));

	//ImGui::BeginListBox("test", ImVec2(25, 25));
	ImGui::Begin("Add Entity");
	//ImGui::EndListBox();
	static std::string EntityName = "Entity";
	static float EntityPos[2] = {m_Window.getSize().x / 2.0f, m_Window.getSize().y / 2.0f };
	ImGui::InputText("Entity Name", &EntityName);
	ImGui::InputFloat2("Entity Position", EntityPos);
	if(ImGui::Button("Add"))
	{
		CurrentScene()->AddEntityAtRuntime(EntityName, Vec2(EntityPos[0], EntityPos[1]));
	}
	const char* filters = "Source files Image files (*.png *.gif *.jpg *.jpeg){.png,.gif,.jpg,.jpeg},.md, (*.cpp *.h *.hpp){.cpp,.h,.hpp}";
	if (ImGui::Button("Open Content Drawer"))
	{
		if(m_ShowContentDrawer)
		{
			m_ShowContentDrawer = false;
			ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", filters, ".");
		}
		else
		{
			m_ShowContentDrawer = true;
			ImGuiFileDialog::Instance()->Close();
		}
	}

	ImGui::End();

	ImGui::Begin(m_CurrentMode.c_str());
	if (ImGui::Button(m_Button.c_str()))
	{
		if(m_EditorMode)
		{
			m_EditorMode = false;
			m_CurrentMode = "PlayMode";
			m_Button = "Stop";
		}
		else
		{
			m_EditorMode = true;
			m_CurrentMode = "EditorMode";
			m_Button = "Play";
		}
	}
	if (ImGui::Button("Move"))
	{
		if(m_MoveMode)
		{
			m_MoveMode = false;
			m_TransformStatus = "Move";
		}
		else
		{
			m_MoveMode = true;
			m_TransformStatus = "Free";
		}
	  // open Dialog with Pane
	}
	ImGui::Text(("Transform Mode: " + m_TransformStatus).c_str());
	ImGui::End();


	//FileDialog

	// display and action if ok
	if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
	{
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
			std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
			std::string filter = ImGuiFileDialog::Instance()->GetCurrentFilter();
			// here convert from string because a string was passed as a userData, but it can be what you want
			std::string userDatas;
			if (ImGuiFileDialog::Instance()->GetUserDatas())
				userDatas = std::string((const char*)ImGuiFileDialog::Instance()->GetUserDatas());
			auto selection = ImGuiFileDialog::Instance()->GetFilePathName();

			// action
			m_ImagePath = selection;

		}
		// close
		ImGuiFileDialog::Instance()->Close();
	}


	if (CurrentScene()->m_SelectedEntity && CurrentScene()->m_SelectedEntity->isActive())
	{
		ImGui::Begin(std::format("Entity: {}", CurrentScene()->m_SelectedEntity->tag()).c_str());


		if (CurrentScene()->m_SelectedEntity->HasComponent<CTransform>())
		{
			std::vector<const char*> strings;
			const char* arr0[] = { "Transform", "Sprite", "Animation", "BoundingBox", "Gravity", "Lifespan", "State" };

			if (!CurrentScene()->m_SelectedEntity->HasComponent<CSprite>())
			{
				strings.push_back(arr0[1]);
			}
			if (!CurrentScene()->m_SelectedEntity->HasComponent<CAnimation>())
			{
				strings.push_back(arr0[2]);
			}
			if (!CurrentScene()->m_SelectedEntity->HasComponent<CBoundingBox>())
			{
				strings.push_back(arr0[3]);
			}
			if (!CurrentScene()->m_SelectedEntity->HasComponent<CGravity>())
			{
				strings.push_back(arr0[4]);
			}
			if (!CurrentScene()->m_SelectedEntity->HasComponent<CLifespan>())
			{
				strings.push_back(arr0[5]);
			}
			if (!CurrentScene()->m_SelectedEntity->HasComponent<CState>())
			{
				strings.push_back(arr0[6]);
			}

			static int selectedItem = 0;
			ImGui::Text("Add Component");
			if (ImGui::ListBox("Component", &selectedItem, strings.data(), strings.size()))
			{
				CurrentScene()->AddComponentAtRuntime(CurrentScene()->m_SelectedEntity, strings.at(selectedItem));
				//log(strings.at(selectedItem)<< " Component Added");

			}
			float matrixTranslation[2] = { CurrentScene()->m_SelectedEntity->GetComponent<CTransform>().pos.x, CurrentScene()->m_SelectedEntity->GetComponent<CTransform>().pos.y },
				  matrixRotation[1] = { CurrentScene()->m_SelectedEntity->GetComponent<CTransform>().angle },
				  matrixScale[2] = { CurrentScene()->m_SelectedEntity->GetComponent<CTransform>().scale.x, CurrentScene()->m_SelectedEntity->GetComponent<CTransform>().scale.y };
			
			ImGui::InputFloat2("Tr", matrixTranslation);
			ImGui::InputFloat("Rt", matrixRotation);
			ImGui::InputFloat2("Sc", matrixScale);

			ImGui::Text(std::format("{} Transform Component", CurrentScene()->m_SelectedEntity->tag()).c_str());
			ImGui::SliderFloat2("Position", matrixTranslation, -5000, 5000);
			ImGui::SliderFloat2("Scale", matrixScale, 1, 5);
			ImGui::SliderFloat("Angle", matrixRotation, 0, 360);
			CurrentScene()->m_SelectedEntity->GetComponent<CTransform>().pos = { matrixTranslation[0], matrixTranslation[1] };
			CurrentScene()->m_SelectedEntity->GetComponent<CTransform>().scale = { matrixScale[0], matrixScale[1] };
			CurrentScene()->m_SelectedEntity->GetComponent<CTransform>().angle = { matrixRotation[0] };

		}
		if (CurrentScene()->m_SelectedEntity->HasComponent<CSprite>())
		{
			auto& sSprite = CurrentScene()->m_SelectedEntity->GetComponent<CSprite>().sprite;
			int r[2] = { sSprite.getOrigin().x, sSprite.getOrigin().y };
			sf::Texture texture;
			/*std::string ip = m_Asset.GetAssetPath()*/
			ImGui::Text(std::format("{} Sprite Component", CurrentScene()->m_SelectedEntity->tag()).c_str());
			ImGui::Text("SpriteTexture");
			ImGui::Text(std::to_string((CurrentScene()->m_SelectedEntity->GetEntityID())).c_str());
			ImGui::Image(sSprite);
			ImGui::InputText("Texture Name", &m_TextureName);
			ImGui::InputText("ImagePath", &m_ImagePath, 80);
			ImGui::SliderInt2("Origin", r, -50, 50);
			if (ImGui::Button("RenderImage"))
			{
				if (m_Asset.AddTexture(std::to_string(CurrentScene()->m_SelectedEntity->GetEntityID()), m_ImagePath))
				{
					CurrentScene()->m_SelectedEntity->GetComponent<CSprite>().textureName = m_TextureName;
					sSprite.setTexture(m_Asset.GetTexture(std::to_string(CurrentScene()->m_SelectedEntity->GetEntityID())));
				}
			}
			sSprite.setOrigin((float)r[0], (float)r[1]);
			if (ImGui::Button("Remove Sprite Component"))
			{
				CurrentScene()->m_SelectedEntity->RemoveComponent<CSprite>();
			}

		}
		else if(CurrentScene()->m_SelectedEntity->HasComponent<CAnimation>())
		{
			auto& ey = CurrentScene()->m_SelectedEntity->GetComponent<CAnimation>().animation.GetSprite();
			int r[2] = { ey.getOrigin().x, ey.getOrigin().y };
			ImGui::Text("SpriteTexture");
			//ImGui::
			ImGui::Image(CurrentScene()->m_SelectedEntity->GetComponent<CAnimation>().animation.GetSprite());
			ImGui::SliderInt2("Origin", r, -50, 50);
			ey.setOrigin((float)r[0], (float)r[1]);
			if (ImGui::IsItemFocused())
			{
				ImGui::SetWindowSize(ImVec2(10, 10));
			}

			if (ImGui::Button("Remove Animation Component"))
			{
				CurrentScene()->m_SelectedEntity->RemoveComponent<CAnimation>();
			}
		}
		if(CurrentScene()->m_SelectedEntity->HasComponent<CBoundingBox>())
		{
			ImGui::Text(std::format("{} BoundingBox Component", CurrentScene()->m_SelectedEntity->tag()).c_str());
			int q[2] = { CurrentScene()->m_SelectedEntity->GetComponent<CBoundingBox>().size.x, CurrentScene()->m_SelectedEntity->GetComponent<CBoundingBox>().size.y };
			ImGui::SliderInt2("BoundingBox", q, -100, 100);
			CurrentScene()->m_SelectedEntity->GetComponent<CBoundingBox>().size = { (float)q[0], (float)q[1] };
			CurrentScene()->m_SelectedEntity->GetComponent<CBoundingBox>().halfSize = { (float)q[0] / 2.0f, (float)q[1] / 2.0f };
			if (ImGui::Button("Remove Bounding Box Component"))
			{
				CurrentScene()->m_SelectedEntity->RemoveComponent<CBoundingBox>();
			}
		}
		if (CurrentScene()->m_SelectedEntity->HasComponent<CAnimation>())
		{
			ImGui::Begin("Animation Editor");
			ImGui::Text("Current Sprite Frame");
			ImGui::Image(CurrentScene()->m_SelectedEntity->GetComponent<CAnimation>().animation.GetSprite());
			ImGui::Text("Update Animation After Frame");
			ImGui::InputInt("Frame", ((int*)&CurrentScene()->m_SelectedEntity->GetComponent<CAnimation>().animation.m_Speed));
			ImGui::End();
		}
		if (ImGui::Button("Remove Entity"))
		{
			CurrentScene()->m_SelectedEntity->destroy();
		}
		ImGui::End();
	}
	else
	{
		ImGui::Begin("Entity: Properties");
		ImGui::Text("Entity Attributes");
		ImGui::End();
	}
	ImGui::PopStyleColor(2);
	ImGui::SFML::Render(m_Window);
}

void GameEngine::init(const std::string& Path)
{
	ImGui::CreateContext();
	ImGui::SFML::Init(m_Window);
	m_Serializer.DeSerializeResource("res/CStellInit.yml", m_Asset);

	//m_TransformGizmoX = m_EditorEntityManager.AddEntity("TransformGizmoX");
	//m_TransformGizmoY = m_EditorEntityManager.AddEntity("TransformGizmoY");
	//m_TransformGizmoX->AddComponent<CTransform>(Vec2(m_Window.getSize().x, m_Window.getSize().y));
	//m_TransformGizmoX->GetComponent<CTransform>().scale = { 1 / 16.0f, 1 / 16.0f };
	//m_TransformGizmoX->AddComponent<CSprite>(m_Asset.GetTexture("GizmoAxisX"));
	//m_TransformGizmoX->GetComponent<CSprite>().sprite.setOrigin(0, m_Asset.GetTexture("GizmoAxisX").getSize().y / 2.0f);
	//m_TransformGizmoX->AddComponent<CBoundingBox>(Vec2(m_Asset.GetTexture("GizmoAxisX").getSize().x * 0.0625,
	//	m_Asset.GetTexture("GizmoAxisX").getSize().y * 0.03125));
	//m_TransformGizmoX->AddComponent<CState>();
	//m_TransformGizmoY->AddComponent<CTransform>(Vec2(m_Window.getSize().x, m_Window.getSize().y));
	//m_TransformGizmoY->GetComponent<CTransform>().scale = { 1 / 16.0f, 1 / 16.0f };
	//m_TransformGizmoY->AddComponent<CSprite>(m_Asset.GetTexture("GizmoAxisY"));
	//m_TransformGizmoY->GetComponent<CSprite>().sprite.setOrigin(m_Asset.GetTexture("GizmoAxisY").getSize().x / 2.0f,
	//															m_Asset.GetTexture("GizmoAxisY").getSize().y);
	//m_TransformGizmoY->AddComponent<CBoundingBox>(Vec2(m_Asset.GetTexture("GizmoAxisY").getSize().x * 0.03125,
	//	m_Asset.GetTexture("GizmoAxisY").getSize().y * 0.0625));
	//m_TransformGizmoY->AddComponent<CState>();

	auto image = sf::Image{};
	image.loadFromFile("res/Texture/DefaultSprite.png");
	m_Window.create(sf::VideoMode(1280, 768), "Constellation Engine SFML");
	m_Window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
	m_Window.setFramerateLimit(74);

	ChangeScene("GameMenu", std::make_shared<Scene_GameMenu>(this, "res/Level1_Resource.yml", "res/GameMenuEntity.yml"));
}

void GameEngine::update()
{
	auto start = std::chrono::system_clock::now();
	// Some computation here
	
	sUserInput();
	CurrentScene()->update();
	if (CurrentScene()->m_SelectedEntity)
	{
		GizmoAction();
	}
	RenderImGui();
	m_Window.display();
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	m_DeltaTime = elapsed_seconds.count();

	debug();
}

void GameEngine::sUserInput()
{
	m_MousePos = { (float)sf::Mouse::getPosition(m_Window).x, (float)sf::Mouse::getPosition(m_Window).y };
	while (m_Window.pollEvent(m_Event))
	{
		CurrentScene()->ProcessImGuiEvent();
		if (m_Event.type == sf::Event::Closed)
		{
			quit();
		}
		if(m_Event.type == sf::Event::KeyPressed)
		{
			if (m_Event.key.code == sf::Keyboard::X)
			{
				//std::cout << "ScreenShot Saved " << "test.png" << std::endl;
				sf::Texture texture;
				texture.create(m_Window.getSize().x, m_Window.getSize().y);
				texture.update(m_Window);
				if (texture.copyToImage().saveToFile("test.png"))
				{
					//std::cout << "ScreenShot Saved " << "test.png" << std::endl;
				}
			}
		}

		if (m_Event.type == sf::Event::KeyPressed || m_Event.type == sf::Event::KeyReleased ||
			m_Event.type == sf::Event::MouseButtonPressed /*|| m_Event.type == sf::Event::MouseButtonReleased*/)
		{
			// If the scene does not have an action associated with this key, skip the event
			if (CurrentScene()->GetActionMap().find(m_Event.key.code) == CurrentScene()->GetActionMap().end() &&
				CurrentScene()->GetActionMapMouse().find(m_Event.mouseButton.button) == CurrentScene()->GetActionMapMouse().end())
			{
				continue;
			}

			// Determine start or end action by whether it was key press or release
			const std::string ActionType = (m_Event.type == sf::Event::KeyPressed) ? "Start" : "End";

			// Look up the action by whether it was key press or release
			if (CurrentScene()->GetActionMapMouse().contains(m_Event.mouseButton.button) && m_Event.key.control)
			{
				CurrentScene()->sSceneEditorAction(Action(CurrentScene()->GetActionMapMouse().at(m_Event.mouseButton.button), ActionType));
				CurrentScene()->sDoAction(Action(CurrentScene()->GetActionMapMouse().at(m_Event.mouseButton.button), ActionType));
			}
			else if (CurrentScene()->GetActionMap().contains(m_Event.key.code) && !m_Event.key.control)
			{
				CurrentScene()->sSceneEditorAction(Action(CurrentScene()->GetActionMap().at(m_Event.key.code), ActionType));
				CurrentScene()->sDoAction(Action(CurrentScene()->GetActionMap().at(m_Event.key.code), ActionType));
			}
			//CurrentScene()->sDoAction(Action(CurrentScene()->GetActionMap().at(102), ActionType));
		}
	}
}

std::shared_ptr<Scene> GameEngine::CurrentScene()
{
	return m_SceneMap[m_CurrentScene];
}


void GameEngine::ChangeScene(const std::string& SceneName, std::shared_ptr<Scene> Scene, bool EndCurrentScene)
{
	m_SceneMap[SceneName] = Scene;
	m_CurrentScene = SceneName;
}


const void GameEngine::SelectEntity(std::shared_ptr<Entity>& e)
{
	if (e->GetComponent<CState>().mouseHover)
	{
		if (e->GetComponent<CState>().selected)
		{
			e->GetComponent<CState>().selected = false;
		}
		else
		{
			m_PreviousSelectedEntity = m_SelectedEntity;
			e->GetComponent<CState>().selected = true;
			m_SelectedEntity = e;
		}
		if (m_PreviousSelectedEntity)
		{
			m_PreviousSelectedEntity->GetComponent<CState>().selected = false;
		}
	}
}

void GameEngine::run()
{
	while (IsRunning())
	{
		update();
	}
}

void GameEngine::quit()
{
	m_Running = false;
}

void GameEngine::debug()
{
}

inline void GameEngine::InfosPane(const char* vFilter, IGFDUserDatas vUserDatas, bool* vCantContinue)
{
	ImGui::TextColored(ImVec4(0, 1, 1, 1), "Infos Pane");
	ImGui::Text("Selected Filter : %s", vFilter);
	if (vUserDatas)
		ImGui::Text("UserDatas : %s", vUserDatas);
	ImGui::Checkbox("if not checked you cant validate the dialog", &canValidateDialog);
	if (vCantContinue)
		*vCantContinue = canValidateDialog;
}

sf::RenderWindow& GameEngine::Window()
{
	return m_Window;
}

Asset& GameEngine::GetAssets()
{
	// TODO: insert return statement here
	return m_Asset;
}

bool GameEngine::IsRunning()
{
	//return m_Running && m_Window.isOpen();
	return m_Running;
}
