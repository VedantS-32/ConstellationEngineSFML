#include "Serializer.h"
#include "Entity.h"
#include "Scene.h"
#include "Asset.h"
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <format>

#define cppstr as<std::string>()
#define cppint as<int>()
#define cppfloat as<float>()

void Serializer::Serialize(Scene& scene)
{
	YAML::Node ResourceRoot;
	ResourceRoot["CStell"] = "SceneResource";

	YAML::Node EntityRoot;
	EntityRoot["CStell"] = "SceneEntity";

	for(auto& e : scene.m_EntityManager.GetEntities())
	{
		YAML::Node Resource;
		YAML::Node Entity;

		Entity["Name"] = e->tag();

		//Animation
		if (e->HasComponent<CAnimation>())
		{
			auto& ec = e->GetComponent<CAnimation>().animation;
			YAML::Node AnimationPreview;
			AnimationPreview["Name"] = ec.m_EntityTag;
			AnimationPreview["Texture"] = ec.m_EntityTag;
			AnimationPreview["FrameCount"] = 1;
			Entity["Animation"].push_back(AnimationPreview);

			for(auto& l : ec.GetAnimationList())
			{
				YAML::Node Animation;
				Animation["Name"] = l;
				Animation["Texture"] = l;
				Animation["FrameCount"] = ec.GetAnimationFrameCount().at(l);
				Entity["Animation"].push_back(Animation);
			}
		}

		// Input
		if (e->HasComponent<CInput>())
		{
			YAML::Node Input;
			Input["Has"] = true;
			Entity["Input"].push_back(Input);
		}

		// Sprite
		if (e->HasComponent<CSprite>())
		{
			YAML::Node Sprite;
			auto& ec = e->GetComponent<CSprite>();
			Sprite["ox"] = ec.origin.x;
			Sprite["oy"] = ec.origin.y;
			Sprite["Texture"] = ec.textureName;
			Entity["Sprite"].push_back(Sprite);

			Resource["Attribute"] = "Texture";
			Resource["Name"] = ec.textureName;
			//Resource["Path"] = scene.
		}

		// Transform
		if (e->HasComponent<CTransform>())
		{
			YAML::Node Transform;
			auto& ec = e->GetComponent<CTransform>();
			Transform["x"] = ec.pos.x;
			Transform["y"] = ec.pos.y;
			Transform["sx"] = ec.scale.x;
			Transform["sy"] = ec.scale.y;
			Transform["a"] = ec.angle;
			Entity["Transform"].push_back(Transform);
		}

		// BoundingBox
		if (e->HasComponent<CBoundingBox>())
		{
			YAML::Node BoundingBox;
			auto& ec = e->GetComponent<CBoundingBox>();
			BoundingBox["x"] = ec.size.x;
			BoundingBox["y"] = ec.size.y;
			BoundingBox["hx"] = ec.halfSize.x;
			BoundingBox["hy"] = ec.halfSize.y;
			BoundingBox["Dynamic"] = ec.dynamic;
			Entity["BoundingBox"].push_back(BoundingBox);
		}

		// Gravity
		if (e->HasComponent<CGravity>())
		{
			YAML::Node Gravity;
			Gravity["g"] = 0;
			Entity["Gravity"].push_back(Gravity);
		}

		// State
		if (e->HasComponent<CState>())
		{
			YAML::Node State;
			auto& ec = e->GetComponent<CState>();
			State["State"] = ec.state;
			Entity["State"].push_back(State);
		}

		// Commit to EntityRoot
		EntityRoot["Entity"].push_back(Entity);
		//console_log(EntityRoot);
	}


	// Output
	std::string SaveName = std::format("res/{}Entity.yml", scene.m_Game->m_CurrentScene);
	std::ofstream out(SaveName);
	out << EntityRoot;
	out.close();
	console_log("Scene Saved");
}

void Serializer::DeSerializeResource(std::string path, Asset& asset)
{
	YAML::Node Config = YAML::LoadFile(path);
	if (Config["CStell"].as<std::string>() == "EditorResource")
	{
		for (int i = 0; i < Config["Resource"].size(); i++)
		{	
			asset.LoadFromFile(Config["Resource"][i]["Attribute"].as<std::string>(),
							   Config["Resource"][i]["Name"].as<std::string>(),
							   Config["Resource"][i]["Path"].as<std::string>());
		}
	}
	if (Config["CStell"].as<std::string>() == "SceneResource")
	{
		for (int i = 0; i < Config["Resource"].size(); i++)
		{
			asset.LoadFromFile(Config["Resource"][i]["Attribute"].as<std::string>(),
				Config["Resource"][i]["Name"].as<std::string>(),
				Config["Resource"][i]["Path"].as<std::string>());
		}
	}
}

void Serializer::DeSerializeEntity(Scene& scene, std::string path)
{
	YAML::Node Config = YAML::LoadFile(path);
	if (Config["CStell"].as<std::string>() == "SceneEntity")
	{
		auto c = Config["Entity"];
		for (int i = 0; i < c.size(); i++)
		{
			auto& e = scene.AddEntityAtInit(c[i]["Name"].as<std::string>());
			if (c[i]["Animation"])
			{
				auto b = c[i]["Animation"];
				auto& a = e->AddComponent<CAnimation>(Animation(b[0]["Name"].as<std::string>(),
					scene.m_Asset.GetTexture(b[0]["Texture"].as<std::string>())), false);
				for (int i = 1; i < b.size(); i++)
				{
					a.animation.AddAnimation(b[i]["Name"].cppstr,
						scene.m_Asset.GetTexture(b[i]["Texture"].cppstr), b[i]["FrameCount"].as<int>());
				}
			}
			if (c[i]["Transform"])
			{
				auto b = c[i]["Transform"];
				e->AddComponent<CTransform>(Vec2(b[0]["x"].cppfloat, b[0]["y"].cppfloat),
											Vec2(b[0]["sx"].cppfloat, b[0]["sy"].cppfloat),
											b[0]["a"].cppfloat);
			}
			if (c[i]["BoundingBox"])
			{
				auto b = c[i]["BoundingBox"];
				e->AddComponent<CBoundingBox>(Vec2(b[0]["x"].cppint, b[0]["y"].cppint), b[0]["Dynamic"].as<bool>());
			}
			if (c[i]["Gravity"])
			{
				auto b = c[i]["Gravity"];
				e->AddComponent<CGravity>(b[0]["g"].as<float>());
			}
			if (c[i]["State"])
			{
				auto b = c[i]["State"];
				e->AddComponent<CState>(b[0]["State"].cppstr);
			}
			if (c[i]["Input"])
			{
				auto b = c[i]["Input"];
				e->AddComponent<CInput>();
			}
			if (c[i]["Sprite"])
			{
				auto b = c[i]["Sprite"];
				auto& d = e->AddComponent<CSprite>(scene.m_Asset.GetTexture(b[0]["Texture"].cppstr), b[0]["Texture"].cppstr);
				d.origin.x = b[0]["ox"].cppfloat;
				d.origin.y = b[0]["oy"].cppfloat;
				d.sprite.setOrigin(d.origin.x, d.origin.y);
			}
			if (c[i]["Lifespan"])
			{
				auto b = c[i]["Lifespan"];
				e->AddComponent<CLifespan>(b[0]["Lifespan"].cppint, b[0]["FrameCreated"].cppint);
			}
			if (c[i]["Name"].as<std::string>() == "Player")
			{
				scene.m_Player = e;
			}
		}
	}
}
