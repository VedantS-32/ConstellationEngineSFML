#pragma once

#include <vector>
#include <memory>
#include <map>
#include <string>
#include "Entity.h"

//class Entity;

typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager
{
private:
	friend class Serializer;
	EntityVector m_Entities;
	EntityVector m_AddQueue;
	EntityMap m_EntityMap;
	size_t m_TotalEntities = 0;
	
public:
	EntityManager();
	void Update();
	std::shared_ptr<Entity> AddEntity(const std::string& tag);
	const EntityVector& GetEntities();
	const EntityVector& GetEntities(const std::string& tag);
	void RemoveDeadEntities(EntityVector& entity);

};