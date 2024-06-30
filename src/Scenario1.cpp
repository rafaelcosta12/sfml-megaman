#include "Scenario1.hpp"
#include <iostream>

Scenario1::Scenario1(b2World* world, Player* player, float px, float py) : GameObject(world)
{
    name = "Scenario1";
    camera = new Camera(world, player->getPosition().x, player->getPosition().y);
    this->player = player;

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

void Scenario1::addGroundFixture(b2Vec2 *box)
{
    b2Vec2 points[4];
    for (int i = 0; i < 4; i++)
    {
        points[i].Set(box[i].x * 0.05f, -box[i].y * 0.05f);
        points[i] -= body->GetPosition();
    }
    b2PolygonShape dynamicBox;
    dynamicBox.Set(points, 4);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.friction = 1.0f;
    fixtureDef.restitution = 0.0f;
    fixtureDef.density = 100.0f;
    
    auto fixture = body->CreateFixture(&fixtureDef);
    fixtures.push_back(fixture);
}

Scenario1::~Scenario1()
{
}

void Scenario1::createShape()
{
    b2Vec2 box[4];
    box[0].Set(1, 1985);
    box[1].Set(1024, 1985);
    box[2].Set(1024, 2048);
    box[3].Set(1, 2048);
    addGroundFixture(box);
    box[0].Set(257, 1953);
    box[1].Set(384, 1953);
    box[2].Set(384, 1985);
    box[3].Set(257, 1985);
    addGroundFixture(box);
    box[0].Set(289, 1922);
    box[1].Set(384, 1922);
    box[2].Set(384, 1953);
    box[3].Set(289, 1953);
    addGroundFixture(box);
    box[0].Set(321, 1889);
    box[1].Set(384, 1889);
    box[2].Set(384, 1921);
    box[3].Set(321, 1921);
    addGroundFixture(box);
}

void Scenario1::update(float dt, sf::RenderWindow& window)
{
    player->update(dt, window);
    camera->update(dt, window);
    camera->setCenter(player->getPosition());
}

void Scenario1::processEvents(sf::Event event, sf::RenderWindow &window)
{
    player->processEvents(event, window);
    camera->processEvents(event, window);
}

void Scenario1::render(sf::RenderWindow& window)
{
    window.draw(sprite);
    camera->render(window);
    player->render(window);
    GameObject::render(window);
}
