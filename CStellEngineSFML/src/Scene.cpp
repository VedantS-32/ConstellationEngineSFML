#include "Scene.h"

void Scene::OnEnd()
{
}

void Scene::setPaused(bool Paused)
{
}

Scene::Scene()
{
}

Scene::Scene(GameEngine* GEngine)
	: m_Game(GEngine)
{
}

Scene::Scene(GameEngine* GEngine, std::string ResourcePath, std::string EntityPath)
	:m_Game(GEngine), m_ResourcePath(ResourcePath), m_EntityPath(EntityPath)
{
}

//void Scene::Update()
//{
//}

//void Scene::sRender()
//{
//}

void Scene::DoAction(const Action& action)
{
	sDoAction(action);
}

void Scene::Simulate(const size_t Frames)
{
}

void Scene::RegisterAction(sf::Keyboard::Key InputKey, const std::string& ActionName)
{
	m_ActionMap[InputKey] = ActionName;
}

void Scene::RegisterAction(sf::Mouse::Button InputKey, const std::string& ActionName)
{
	m_ActionMapMouse[InputKey] = ActionName;
}

void Scene::InitScene()
{
	m_EntityManager = EntityManager();
	m_Asset.AddTexture("DefaultSprite", m_Game->GetAssets().GetTexture("DefaultSprite"));
	m_Game->m_Serializer.DeSerializeResource(m_ResourcePath, m_Asset);
	m_Game->m_Serializer.DeSerializeEntity(*this, m_EntityPath);

	InitEditorKeyMap();

	//m_View.setViewport(sf::FloatRect(0.0f, 0.0f, 1280/m_Game->m_ViewPortWidth, 768/m_Game->m_ViewPortHeight));

	//AddEntityAtInit(scene, "Test");
	//AddEntityAtRuntime("Test", Vec2(200, 200));
}

void Scene::InitEditorKeyMap()
{
	RegisterAction(sf::Keyboard::P, "Pause");
	RegisterAction(sf::Keyboard::Escape, "Quit");
	RegisterAction(sf::Keyboard::T, "ToggleTexture");
	RegisterAction(sf::Keyboard::C, "ToggleCollision");
	RegisterAction(sf::Keyboard::Y, "ToggleGrid");
	RegisterAction(sf::Keyboard::F, "Debug");

	RegisterAction(sf::Keyboard::G, "Move");
	RegisterAction(sf::Keyboard::F3, "Save");

	RegisterAction(sf::Keyboard::Q, "Play");
	RegisterAction(sf::Mouse::Left, "SelectEntity");
}

void Scene::ProcessImGuiEvent()
{
	ImGui::SFML::ProcessEvent(m_Game->Window(), m_Game->m_Event);
}

void Scene::SelectEntity()
{
	for (auto& e : m_EntityManager.GetEntities())
	{
		if(e->GetComponent<CState>().mouseHover)
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

			if (m_PreviousSelectedEntity != m_SelectedEntity && m_PreviousSelectedEntity != nullptr)
			{
				m_PreviousSelectedEntity->GetComponent<CState>().selected = false;
			}
		}
	}
}

const std::shared_ptr<Entity> Scene::AddEntityAtInit(std::string Name)
{
	auto e = m_EntityManager.AddEntity(Name);
	
	return e;
}

void Scene::AddEntityAtRuntime(std::string Name, Vec2 Position)
{
	auto e = m_EntityManager.AddEntity(Name);
	e->AddComponent<CTransform>(Position);
	e->AddComponent<CSprite>(m_Game->GetAssets().GetTexture("DefaultSprite"), "DefaultSprite");
	auto& f = e->GetComponent<CSprite>();
	e->GetComponent<CTransform>().scale = { 2.0f, 2.0f };
	e->AddComponent<CBoundingBox>(Vec2(f.spriteTexture.getSize().x * e->GetComponent<CTransform>().scale.x,
									   f.spriteTexture.getSize().x * e->GetComponent<CTransform>().scale.y));
	f.origin.x = e->GetComponent<CBoundingBox>().size.x / (2.0f * e->GetComponent<CTransform>().scale.x);
	f.origin.y = e->GetComponent<CBoundingBox>().size.x / (2.0f * e->GetComponent<CTransform>().scale.y);
	f.sprite.setOrigin(f.origin.x, f.origin.y);
	e->AddComponent<CState>();
	SelectEntity();
	console_log(Name << "Added");
}

void Scene::AddComponentAtRuntime(std::shared_ptr<Entity> e, std::string CName)
{
	if (CName == "Sprite")
	{
		auto &s = e->AddComponent<CSprite>(m_Game->GetAssets().GetTexture("DefaultSprite"), "DefaultSprite");
		e->GetComponent<CTransform>().scale = { 2.0f, 2.0f };
		s.sprite.setOrigin(s.spriteTexture.getSize().x / 2.0f, s.spriteTexture.getSize().y / 2.0f);
	}
	if (CName == "Animation")
	{
		e->AddComponent<CAnimation>(Animation("Preview", m_Game->GetAssets().GetTexture("DefaultSprite")));
	}
	if (CName == "BoundingBox")
	{
		e->AddComponent<CBoundingBox>();
	}
	if (CName == "Gravity")
	{
		e->AddComponent<CGravity>();
	}
	if (CName == "Lifespan")
	{
		e->AddComponent<CLifespan>();
	}
	if (CName == "State")
	{
		e->AddComponent<CState>();
	}
}

void Scene::UpdateAttribute()
{
	m_View.zoom(m_Game->m_GlobalZoom);
	m_Game->m_GlobalZoom = 1.0f;
	//m_View.setViewport(sf::FloatRect(0.0f, (768 - m_Game->m_ViewPortHeight) / 768, m_Game->m_ViewPortWidth / 1280, 1));
	//m_View.setViewport(sf::FloatRect(0.0f, (768 - m_Game->m_ViewPortHeight) / 768, m_Game->m_ViewPortWidth / 1280, 1));
}

void Scene::SaveScene()
{
	m_Game->m_Serializer.Serialize(*this);
}

size_t Scene::Width() const
{
	return m_Game->Window().getSize().x;
}

size_t Scene::Height() const
{
	return m_Game->Window().getSize().y;
}

size_t Scene::CurrentFrame() const
{
	return m_CurrentFrame;
}

void Scene::sSceneSystemUpdate()
{
	sGravityUpdate();
	sCollision();
	sSceneSystemRender();
}

void Scene::sGravityUpdate()
{
	for (auto& e : m_EntityManager.GetEntities())
	{
		auto& entityTransform = e->GetComponent<CTransform>();
		entityTransform.previousPos = entityTransform.pos;
		if (e->HasComponent<CGravity>())
		{
			m_Physics.Update(e, 0.015f);
		}
		entityTransform.velocity = { 0, 0 };

		//Particle Update
		if (e->tag() == "Brick Particle")
		{
			e->GetComponent<CTransform>().angle += 20;
		}
	}
}

void Scene::sCollision()
{
	Vec2 overlap, previousOverlap;
	//mousePos = { (float)sf::Mouse::getPosition(m_Game->Window()).x, (float)sf::Mouse::getPosition(m_Game->Window()).y };
	for (auto& e : m_EntityManager.GetEntities())
	{
		if (e->GetComponent<CBoundingBox>().dynamic)
		{
			for (auto& f : m_EntityManager.GetEntities())
			{
				m_Physics.GetOverlappingEntity(f, m_Game->m_MousePos);
				if (f->HasComponent<CBoundingBox>() && e->HasComponent<CBoundingBox>() && f->tag() != "Player")
				{
					if (e->GetEntityID() != f->GetEntityID())
					{
						previousOverlap = m_Physics.GetPreviousOverlap(e, f);
						overlap = m_Physics.GetOverlap(e, f);
						if (overlap.x > 0 && overlap.y > 0)
						{
							if (e->HasComponent<CState>())
							{
								e->GetComponent<CState>().onFloor = true;
							}
							if (previousOverlap.x > 0)
							{
								if (e->GetComponent<CTransform>().pos.y < f->GetComponent<CTransform>().pos.y)
								{
									if (f->GetComponent<CBoundingBox>().dynamic)
									{
										//f->RemoveComponent<CGravity>();
										//f->GetComponent<CTransform>().acceleration = { 0, 0 };
										f->GetComponent<CBoundingBox>().dynamic = false;
									}
									e->GetComponent<CTransform>().pos.y -= overlap.y;
								}
								if (e->GetComponent<CTransform>().pos.y > f->GetComponent<CTransform>().pos.y)
								{
									e->GetComponent<CTransform>().pos.y += overlap.y;
									if (e->tag() == "Player")
									{
										e->GetComponent<CGravity>().jumpAccleration.y += m_Physics.m_Gravity.y;
										//sSpawnParticle(f);
										f->destroy();
									}
								}
							}
							if (previousOverlap.y > 0)
							{
								if (e->GetComponent<CTransform>().pos.x < f->GetComponent<CTransform>().pos.x)
								{
									e->GetComponent<CTransform>().pos.x -= overlap.x;
								}
								if (e->GetComponent<CTransform>().pos.x > f->GetComponent<CTransform>().pos.x)
								{
									e->GetComponent<CTransform>().pos.x += overlap.x;
								}
							}
						}
					}
				}
			}
		}
	}
}

void Scene::sSceneSystemRender()
{
	//Draw all Entity textures and animation
	if (m_DrawTextures)
	{
		for (auto& e : m_EntityManager.GetEntities())
		{
			auto& transform = e->GetComponent<CTransform>();

			if (e->HasComponent<CAnimation>())
			{
				auto& animation = e->GetComponent<CAnimation>().animation;
				animation.GetSprite().setRotation(transform.angle);
				animation.GetSprite().setPosition(transform.pos.x, transform.pos.y);
				animation.GetSprite().setScale(transform.scale.x, transform.scale.y);
				m_Game->Window().draw(animation.GetSprite());
			}

			if (e->HasComponent<CSprite>())
			{
				auto& sSprite = e->GetComponent<CSprite>().sprite;
				sSprite.setRotation(transform.angle);
				sSprite.setPosition(transform.pos.x, transform.pos.y);
				sSprite.setScale(transform.scale.x, transform.scale.y);
				m_Game->Window().draw(sSprite);
			}
		}
	}

	// Draw all entity collision bounding boxes with a rectangle shape
	if (m_DrawCollision)
	{
		for (auto& e : m_EntityManager.GetEntities())
		{
			if (e->HasComponent<CBoundingBox>())
			{
				auto& box = e->GetComponent<CBoundingBox>();
				auto& transform = e->GetComponent<CTransform>();
				sf::RectangleShape rect;
				rect.setSize(sf::Vector2f(box.size.x - 1, box.size.y - 1));
				rect.setOrigin(sf::Vector2f(box.halfSize.x - 1, box.halfSize.y - 1));
				rect.setPosition(transform.pos.x, transform.pos.y);
				rect.setFillColor(sf::Color(0, 0, 0, 0));
				rect.setOutlineColor(sf::Color(255, 255, 255, 255));
				rect.setOutlineThickness(1);
				m_Game->Window().draw(rect);
			}
		}
	}

	// Draw the grid so that students can easily debug
	if (m_DrawGrid)
	{
		float leftX = m_Game->Window().getView().getCenter().x - Width() / 2.0f;
		float rightX = leftX + Width() + m_GridSize.x;
		float nextGridX = leftX - ((int)leftX % (int)m_GridSize.x);

		for (float x = nextGridX; x < rightX; x += m_GridSize.x)
		{
			DrawLine(Vec2(x, 0), Vec2(x, Height()));
		}

		for (float y = 0; y < Height(); y += m_GridSize.y)
		{
			DrawLine(Vec2(leftX, Height()), Vec2(rightX, Height() - y));

			for (float x = nextGridX; x < rightX; x += m_GridSize.x)
			{
				std::string xCell = std::to_string((int)x / (int)m_GridSize.x);
				std::string yCell = std::to_string((int)y / (int)m_GridSize.y);
				/*m_GridText.setString("(" + xCell + ", " + yCell + ", " + std::to_string((int)m_GridSize.x) +
																  ", " + std::to_string((int)m_GridSize.y) + ")");*/
				m_GridText.setString("(" + xCell + ", " + yCell + ")");
				m_GridText.setPosition(x + 3, Height() - y - m_GridSize.y + 2);
				m_Game->Window().draw(m_GridText);
			}
		}
	}

	// Show selected
	for (auto& e : m_EntityManager.GetEntities())
	{
		auto& transform = e->GetComponent<CTransform>();
		if (e->GetComponent<CState>().selected)
		{
			if (e->HasComponent<CBoundingBox>())
			{
				auto& box = e->GetComponent<CBoundingBox>();
				sf::RectangleShape rect;
				rect.setSize(sf::Vector2f(box.size.x - 1, box.size.y - 1));
				rect.setOrigin(sf::Vector2f(box.halfSize.x - 1, box.halfSize.y - 1));
				rect.setPosition(transform.pos.x, transform.pos.y);
				rect.setFillColor(sf::Color(0, 0, 255, 150));
				rect.setOutlineColor(sf::Color::Cyan);
				rect.setOutlineThickness(2);
				m_Game->Window().draw(rect);
			}
		}
		if (e->GetComponent<CState>().mouseHover)
		{
			if (e->HasComponent<CBoundingBox>())
			{
				auto& box = e->GetComponent<CBoundingBox>();
				sf::RectangleShape rect;
				rect.setSize(sf::Vector2f(box.size.x - 1, box.size.y - 1));
				rect.setOrigin(sf::Vector2f(box.halfSize.x - 1, box.halfSize.y - 1));
				rect.setPosition(transform.pos.x, transform.pos.y);
				rect.setFillColor(sf::Color(0, 0, 255, 75));
				rect.setOutlineColor(sf::Color::Cyan);
				rect.setOutlineThickness(2);
				m_Game->Window().draw(rect);
			}
		}
	}
}

void Scene::sSceneEditorAction(const Action& action)
{
	if (action.Type() == "Start")
	{
		if (action.Name() == "ToggleTexture")
		{
			m_DrawTextures = !m_DrawTextures;
			if (m_DrawTextures) std::cout << "Rendering Texture" << std::endl;
		}
		else if (action.Name() == "ToggleCollision")
		{
			m_DrawCollision = !m_DrawCollision;
			if (m_DrawTextures) std::cout << "Rendering Collision Shape" << std::endl;
		}
		else if (action.Name() == "ToggleGrid")
		{
			m_DrawGrid = !m_DrawGrid;
			if (m_DrawTextures) std::cout << "Rendering Grid" << std::endl;
		}
		else if (action.Name() == "Pause") { m_Pause = !m_Pause; }
		else if (action.Name() == "Quit") { OnEnd(); }
		else if (action.Name() == "SelectEntity")
		{
			console_log("LeftClick");
		}
		if (action.Name() == "Play")
		{
			if (m_Game->m_EditorMode)
			{
				m_Game->m_EditorMode = false;
				m_Game->m_Button = "Stop";
			}
			else
			{
				m_Game->m_EditorMode = true;
				m_Game->m_Button = "Play";
			}
		}
		else if (action.Name() == "Debug")
		{
			//sDebug();
		}
		else if (action.Name() == "Save")
		{
			SaveScene();
		}
		else if (action.Name() == "Move")
		{
			if (m_Game->m_MoveMode)
			{
				m_Game->m_MoveMode = false;
				m_Game->m_TransformStatus = "Move";
			}
			else
			{
				m_Game->m_MoveMode = true;
				m_Game->m_TransformStatus = "Free";
			}
		}
	}
	else if (action.Type() == "End")
	{
		if (action.Name() == "SelectEntity")
		{
			SelectEntity();
		}
	}
}

bool Scene::hasEnded() const
{
	return false;
}

const ActionMap& Scene::GetActionMap() const
{
	// TODO: insert return statement here
	return m_ActionMap;
}

const ActionMapMouse& Scene::GetActionMapMouse() const
{
	// TODO: insert return statement here
	return m_ActionMapMouse;
}

void Scene::DrawLine(const Vec2& p1, const Vec2& p2)
{
}
