#include <random>
#include "Physics.h"
#include "Component.h"
#include "Entity.h"

Vec2 Physics::GetOverlap(const std::shared_ptr<Entity>& e,const std::shared_ptr<Entity>& f)
{
    // Return the overlap rectangle size of the bounding boxes of the entity a and b
    Vec2 eV, fV;
    Vec2 eS, fS;
    eV = e->GetComponent<CTransform>().pos;
    eS = e->GetComponent<CBoundingBox>().halfSize;
    fV = f->GetComponent<CTransform>().pos;
    fS = f->GetComponent<CBoundingBox>().halfSize;


    Vec2 delta = { abs(eV.x - fV.x), abs(eV.y - fV.y) };
    m_Overlap = { eS.x + fS.x - delta.x, eS.y + fS.y - delta.y };

    /*if (eV.x < fV.x + fS.x ||
        eV.y < fV.y + fS.y ||
        fV.x < fV.x + eS.x ||
        fV.x < fV.x + eS.x)*/
    if (m_Overlap.x > 0 || m_Overlap.y > 0)
    {
        return m_Overlap;
    }
    return Vec2(0, 0);
}

Vec2 Physics::GetPreviousOverlap(const std::shared_ptr<Entity>& e, const std::shared_ptr<Entity>& f)
{
    // Return the previous overlap rectangle size of the bounding boxes of the entity a and b
    // previous overlap uses the entity's previous position
    Vec2 eV, fV;
    Vec2 eS, fS;
    eV = e->GetComponent<CTransform>().previousPos;
    eS = e->GetComponent<CBoundingBox>().halfSize;
    fV = f->GetComponent<CTransform>().previousPos;
    fS = f->GetComponent<CBoundingBox>().halfSize;
    Vec2 delta = { abs(eV.x - fV.x), abs(eV.y - fV.y) };
    m_PreviousOverlap = { eS.x + fS.x - delta.x, eS.y + fS.y - delta.y };
    if (m_PreviousOverlap.x > 0 || m_PreviousOverlap.y > 0)
    {
        return m_PreviousOverlap;
    }
    return Vec2(0, 0);
}

void Physics::GetOverlappingEntity(const std::shared_ptr<Entity>& e, Vec2 mousePos)
{
    Vec2 eV, eS;
    eV = e->GetComponent<CTransform>().pos;
    eS = e->GetComponent<CBoundingBox>().halfSize;
    Vec2 delta = { abs(eV.x - mousePos.x), abs(eV.y - mousePos.y) };
    m_MouseOverlap = { eS.x - delta.x, eS.y - delta.y };
    if (m_MouseOverlap.x > 0 && m_MouseOverlap.y > 0)
    {
        e->GetComponent<CState>().mouseHover = true;
    }
    else
    {
        e->GetComponent<CState>().mouseHover = false;
    }
}

void Physics::UpdateGravity(const std::shared_ptr<Entity>& e, float dt)
{
    auto& entityTransform = e->GetComponent<CTransform>();
    entityTransform.vectorVelocity = entityTransform.pos - entityTransform.previousPos;
    entityTransform.velocity += entityTransform.acceleration;
    entityTransform.pos += entityTransform.velocity * dt * 100;
    entityTransform.acceleration = { 0.0, 0.0 };
}

void Physics::Update(const std::shared_ptr<Entity>& e, float dt)
{   
    if(e->HasComponent<CGravity>())
    {
        ApplyGravity(e);
        UpdateGravity(e, dt);
    }
}

void Physics::ApplyGravity(const std::shared_ptr<Entity>& e)
{
    e->GetComponent<CTransform>().acceleration += (m_Gravity + e->GetComponent<CGravity>().jumpAccleration);
    if(e->GetComponent<CGravity>().jumpAccleration.y < 0)
    {
        e->GetComponent<CGravity>().jumpAccleration.y += 0.4;
    }
    else
    {
        e->GetComponent<CGravity>().jumpAccleration.y = 0;
    }
    //log(e->GetComponent<CTransform>().acceleration.y);
    //if(e->tag() == "Player")
    //log(m_Gravity.x << ", " << m_Gravity.y);
}


float Physics::RandomNumberGen(float Min, float Max)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(Min, Max); // define the range
    return distr(gen);
}