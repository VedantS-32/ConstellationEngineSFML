#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager()
{
}

// Called at the beginning of each frame by game engine
// Entities added will now be available to use this frame
void EntityManager::Update()
{
	for (auto &e : m_AddQueue)
	{
		m_Entities.push_back(e);
		m_EntityMap[e->tag()].push_back(e);
	}

	m_AddQueue.clear();

	// Remove dead entities from the vector of all entities
	RemoveDeadEntities(m_Entities);

	// Remove dead entities from each vector in the entity map
	// C++17 way of iterating through [key, value] pairs in a map
	for (auto& [tag, entity] : m_EntityMap)
	{
		RemoveDeadEntities(entity);
	}
}

std::shared_ptr<Entity> EntityManager::AddEntity(const std::string& tag)
{
	//Give each entity an increasing integer ID
	auto e = std::make_shared<Entity>(m_TotalEntities++, tag);
	m_AddQueue.push_back(e);
	return e;
}

const EntityVector& EntityManager::GetEntities()
{
	return m_Entities;
}

const EntityVector& EntityManager::GetEntities(const std::string& tag)
{
	return m_EntityMap[tag];
}

void EntityManager::RemoveDeadEntities(EntityVector& entity)
{
	// Use the erase-remove idiom to remove dead entities from the vector
	entity.erase(std::remove_if(entity.begin(), entity.end(), [](const std::shared_ptr<Entity>& e) {
		return !e->isActive();
		}), entity.end());
}
