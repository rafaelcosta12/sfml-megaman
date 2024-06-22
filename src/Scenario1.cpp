#include "Scenario1.hpp"
#include <iostream>

Scenario1::Scenario1(b2World* world, float px, float py) : GameObject(world)
{
    auto sizeX = 100.0f;
    auto sizeY = 2.0f;
    name = "Scenario1";

    // physics
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_staticBody;
    bodyDef.position.Set(px, -py);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    body = world->CreateBody(&bodyDef);
    
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(sizeX, sizeY);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.friction = 1.0f;
    fixtureDef.restitution = 0.0f;
    fixtureDef.density = 100.0f;
    fixture = body->CreateFixture(&fixtureDef);

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
}

Scenario1::~Scenario1()
{
}

void Scenario1::update(float dt, sf::RenderWindow& window)
{
    
}

void Scenario1::render(sf::RenderWindow& window)
{
    window.draw(sprite);
    GameObject::render(window);
}
