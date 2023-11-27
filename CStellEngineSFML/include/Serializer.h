#pragma once
#include <string>
#include <memory>

class Asset;
class Scene;
class EntityManager;
class Entity;

class Serializer
{
public:
	void Serialize(Scene& scene);
	void DeSerializeResource(std::string path, Asset& asset);
	void DeSerializeEntity(Scene& scene, std::string path);
};