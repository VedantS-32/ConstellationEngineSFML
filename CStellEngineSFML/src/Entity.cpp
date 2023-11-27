#include "Entity.h"

Entity::Entity(size_t id, const std::string& tag)
{
    m_id = id;
    m_tag = tag;
}

bool Entity::isActive() const
{
    return m_alive;
}

const std::string& Entity::tag() const
{
    // TODO: insert return statement here
    return m_tag;
}

const size_t Entity::id() const
{
    return size_t();
}

void Entity::destroy()
{
    m_alive = false;
}
