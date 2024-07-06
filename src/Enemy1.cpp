#include "Enemy1.hpp"
#include "imgui.h"

Enemy1::Enemy1(b2World *world, sf::Vector2f spawnPosition) : GameObject(world)
{
    name = "Enemy";
    damage = 10;
    moveSpeed = 1.5;

    guardTimeout = 2;
    readyTimeout = 1;
    walkTimeout  = 5;
    guardTime = guardTimeout;

    animation = new Animation<Enemy1AnimationEnum>("../assets/enemy_1.png", 20, Enemy1AnimationEnum::GUARD);
    animation->addSprites(Enemy1AnimationEnum::GUARD, 0, {1});
    animation->addSprites(Enemy1AnimationEnum::READY, 1, {0.1, 0.5});
    animation->addSprites(Enemy1AnimationEnum::WALK, 2, {0.1, 0.1});

    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.position.Set(spawnPosition.x, -spawnPosition.y);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    bodyDef.fixedRotation = true;
    body = world->CreateBody(&bodyDef);
    
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(19 * 0.05f / 2, 19 * 0.05f / 2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.friction = 1.0f;
    fixtureDef.restitution = 0.0f;
    fixtureDef.density = 100.0f;
    fixtureDef.isSensor = false;
    fixture = body->CreateFixture(&fixtureDef);
}

Enemy1::~Enemy1()
{}

void Enemy1::processEvents(sf::Event event, sf::RenderWindow& window)
{
}

void Enemy1::update(float dt, sf::RenderWindow& window)
{
    auto linearVelocity = body->GetLinearVelocity();
    linearVelocity.x = 0;

    if (animation->getCurrent() == Enemy1AnimationEnum::GUARD)
    {
        guardTime -= dt;
        
        if (guardTime <= 0)
        {
            animation->setAnimation(Enemy1AnimationEnum::READY, true);
            readyTime = readyTimeout;
        }
    }

    if (animation->getCurrent() == Enemy1AnimationEnum::READY)
    {
        readyTime -= dt;

        if (readyTime <= 0)
        {
            animation->setAnimation(Enemy1AnimationEnum::WALK, true);
            walkTime = walkTimeout;
        }
    }
    
    if (animation->getCurrent() == Enemy1AnimationEnum::WALK)
    {
        walkTime -= dt;
        linearVelocity.x = moveSpeed;

        if (walkTime <= 0)
        {
            moveSpeed *= -1;
            animation->invertX();
            animation->setAnimation(Enemy1AnimationEnum::GUARD, true);
            guardTime = guardTimeout;
        }
    }

    body->SetLinearVelocity(linearVelocity);

    animation->update(dt, body);
}

void Enemy1::render(sf::RenderWindow& window)
{
    animation->render(window);
    GameObject::render(window);

    // imgui
    auto pos = body->GetPosition();
    ImGui::Begin("Enemy 1");
    ImGui::Text("Position: (%.3f, %.3f)", pos.x, -pos.y);
    ImGui::InputFloat("Move Speed", &moveSpeed);
    ImGui::InputFloat("Damage", &damage);
    ImGui::InputFloat("Guard Timeout", &guardTimeout);
    ImGui::InputFloat("Ready Timeout", &readyTimeout);
    ImGui::InputFloat("Walk Timeout", &walkTimeout);
    ImGui::End();
}