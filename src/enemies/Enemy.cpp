#include "enemies/Enemy.hpp"
#include "Enemy.hpp"
#include "imgui.h"

Enemy::Enemy(b2World* world, sf::Vector2f spawnPosition) : GameObject(world)
{
    tag = Tag::Enemy;
}

Enemy::~Enemy()
{
}

void Enemy::processEvents(sf::Event event, sf::RenderWindow &window)
{
}

void Enemy::update(float dt, sf::RenderWindow &window)
{
}

void Enemy::render(sf::RenderWindow &window)
{
    animation->render(window);
    GameObject::render(window);

    auto position = body->GetPosition();
    ImGui::Begin(name.c_str());
    ImGui::Text("Position: (%.3f, %.3f)", position.x, -position.y);
    ImGui::InputFloat("Move Speed", &moveSpeed);
    ImGui::InputFloat("Damage", &damage);
    ImGui::InputFloat("HP", &hp);
    ImGui::End();
}

void Enemy::beginContact(GameObject *other, b2Fixture *fixture, b2Fixture *otherFixture)
{
}

void Enemy::endContact(GameObject *other, b2Fixture *fixture, b2Fixture *otherFixture)
{
}

bool Enemy::isDeath()
{
    return hp <= 0;
}

void Enemy::destroy()
{
    world->DestroyBody(body);
}
