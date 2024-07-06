#include "BasicShot.hpp"

BasicShot::BasicShot(b2World* world, sf::Vector2f spanwPosition, bool lookingRight) : GameObject(world)
{
    float side = lookingRight ? 1 : -1;
    damage = 10;
    speed = 10 * side;
    animation = new Animation<BasicShotEnum>("../assets/projectiles.png", 20, BasicShotEnum::ON);
    animation->addSprites(BasicShotEnum::ON, 0, {1});

    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.position.Set(spanwPosition.x + side * 20 * 0.05f, -spanwPosition.y + 2 * 0.05f);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    bodyDef.gravityScale = 0;
    body = world->CreateBody(&bodyDef);
    
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(6 * 0.05f / 2, 6 * 0.05f / 2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.0f;
    fixtureDef.density = 1.0f;
    fixtureDef.isSensor = true;
    fixture = body->CreateFixture(&fixtureDef);
}

BasicShot::~BasicShot() {}

void BasicShot::processEvents(sf::Event event, sf::RenderWindow& window)
{
    
}

void BasicShot::update(float dt, sf::RenderWindow& window)
{
    body->SetLinearVelocity(b2Vec2(speed, 0));
    animation->update(dt, body);
}

void BasicShot::render(sf::RenderWindow& window)
{
    animation->render(window);
    GameObject::render(window);
}