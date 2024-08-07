#include "GameObject.hpp"
#include <iostream>
#include "imgui.h"

GameObject::GameObject(b2World* world)
{
    this->world = world;
    tag = Tag::Any;
}

GameObject::~GameObject()
{
}

void GameObject::processEvents(sf::Event event, sf::RenderWindow& window)
{
}

void GameObject::render(sf::RenderWindow& window)
{
    if (body == NULL)
        return;
    
    for (b2Fixture* i = body->GetFixtureList(); i; i = i->GetNext())
    {
        b2PolygonShape* polygon = static_cast<b2PolygonShape*>(i->GetShape());
        sf::VertexArray polygonShape(sf::PrimitiveType::LineStrip, polygon->m_count + 1);
        
        for (int i = 0; i < polygon->m_count; ++i)
        {
            b2Vec2 globalVertex = body->GetWorldPoint(polygon->m_vertices[i]);
            polygonShape[i].position = sf::Vector2f(globalVertex.x, -globalVertex.y);
            polygonShape[i].color = sf::Color::Green;
        }

        b2Vec2 globalVertex = body->GetWorldPoint(polygon->m_vertices[0]);
        polygonShape[polygon->m_count].position = sf::Vector2f(globalVertex.x, -globalVertex.y);
        polygonShape[polygon->m_count].color = sf::Color::Green;

        window.draw(polygonShape);
    }
}

void GameObject::update(float dt, sf::RenderWindow& window)
{
}

sf::Vector2f GameObject::getPosition()
{
    auto pos = body->GetPosition();
    return sf::Vector2f(pos.x, -pos.y);
}

void GameObject::beginContact(GameObject* other, b2Fixture* fixture, b2Fixture* otherFixture)
{
}

void GameObject::endContact(GameObject* other, b2Fixture* fixture, b2Fixture* otherFixture)
{
}
