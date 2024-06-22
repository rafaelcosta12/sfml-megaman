#include "Box.hpp"
#include <iostream>

Box::Box(b2World* world, float px, float py, float sx, float sy) : GameObject(world)
{
    name = "Box";

    // physics
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.position.Set(px, -py);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    body = world->CreateBody(&bodyDef);
    
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(sx, sy);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.0f;
    fixtureDef.density = 100.0f;
    fixture = body->CreateFixture(&fixtureDef);

    // shape
    shape = sf::RectangleShape(sf::Vector2f(sx * 2, sy * 2));
    shape.setOrigin(sx, sy);

    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Green);
    shape.setOutlineThickness(0.05f);
}

Box::~Box()
{
}

void Box::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    // Obtenha o corpo A e B
    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();

    if (fixture != fixtureA && fixture != fixtureB) return;

    const b2Manifold* manifold = contact->GetManifold();

    // Acessa as forças normais
    for (int i = 0; i < manifold->pointCount; ++i)
    {
        float normalForce = impulse->normalImpulses[i];
        b2Vec2 point = manifold->points[i].localPoint;
        if (point.y <= -0.4f) continue;
    }
}

void Box::render(sf::RenderWindow& window)
{
    // auto pos = body->GetPosition();
    // shape.setPosition(pos.x, -pos.y);
    // shape.setRotation(body->GetAngle() * -(180 / 3.141592653589793238463));
    // window.draw(shape);
    GameObject::render(window);
}
