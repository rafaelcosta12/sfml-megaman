#include "Scenario1.hpp"
#include <iostream>

Scenario1::Scenario1(b2World* world, float px, float py) : GameObject(world)
{
    name = "Scenario1";

    // shape
    sprite = sf::Sprite();
    texture = sf::Texture();
    std::string filename = "../assets/snakeman_stage.png";
    if (!texture.loadFromFile(filename))
    {
        std::cout << "Erro ao abrir textura " + filename << std::endl;
    }
    sprite.setTexture(texture, true);
    sprite.setPosition(0, 0);
    sprite.scale(sf::Vector2f(0.05f, 0.05f));

    // physics
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_staticBody;
    bodyDef.position.Set(sprite.getPosition().x, sprite.getPosition().y);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    body = world->CreateBody(&bodyDef);
    
    // shape
    createShape();
}

Scenario1::~Scenario1()
{
}

void Scenario1::createShape()
{
    std::vector<sf::Vector2f> vertices({
        sf::Vector2f(1, 1986),
        sf::Vector2f(1025, 1986),
        sf::Vector2f(1025, 2049),
        sf::Vector2f(1, 2049),
    });

    b2Vec2 points[vertices.size()];
    for (int i = 0; i < vertices.size(); i++)
    {
        auto v = vertices.at(i);
        points[i].Set(v.x * 0.05f, -v.y * 0.05f);
        points[i] -= body->GetPosition();
    }

    b2PolygonShape dynamicBox;
    dynamicBox.Set(points, vertices.size());
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.friction = 1.0f;
    fixtureDef.restitution = 0.0f;
    fixtureDef.density = 100.0f;
    fixture = body->CreateFixture(&fixtureDef);
}

void Scenario1::update(float dt, sf::RenderWindow& window)
{
    
}

void Scenario1::render(sf::RenderWindow& window)
{
    window.draw(sprite);
    GameObject::render(window);
}
