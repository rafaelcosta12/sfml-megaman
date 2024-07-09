#include "Met.hpp"
#include "imgui.h"
#include <iostream>

Met::Met(b2World *world, sf::Vector2f spawnPosition) : Enemy(world, spawnPosition)
{
    name = "Met (Enemy)";
    tag = Tag::Enemy;
    damage = 10;
    hp = 30;
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

Met::~Met()
{}

void Met::processEvents(sf::Event event, sf::RenderWindow& window)
{
}

void Met::update(float dt, sf::RenderWindow& window)
{
    if (cooldown > 0)
        cooldown -= dt;

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

void Met::render(sf::RenderWindow& window)
{
    Enemy::render(window);

    ImGui::Begin(name.c_str());
    ImGui::InputFloat("Guard Timeout", &guardTimeout);
    ImGui::InputFloat("Ready Timeout", &readyTimeout);
    ImGui::InputFloat("Walk Timeout", &walkTimeout);
    ImGui::End();
}

void Met::beginContact(GameObject *other, b2Fixture *fixture, b2Fixture *otherFixture)
{
    if (other->tag == Tag::PlayerBullet)
    {
        hp -= 10;
        std::cout << "Enemy takes damage: HP " << hp << std::endl;
    }
}

void Met::endContact(GameObject *other, b2Fixture *fixture, b2Fixture *otherFixture)
{
}
