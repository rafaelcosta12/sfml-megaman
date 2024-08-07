#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

enum class Tag { Any, Player, Scenario, Enemy, PlayerBullet };

class GameObject
{
protected:
    b2World* world;
    b2Body* body = NULL;
public:
    std::string name = "unknow";
    Tag tag;
    
    GameObject(b2World* world);
    ~GameObject();
    
    virtual void processEvents(sf::Event event, sf::RenderWindow& window);
    virtual void update(float dt, sf::RenderWindow& window);
    virtual void render(sf::RenderWindow& window);
    virtual sf::Vector2f getPosition();
    virtual void beginContact(GameObject* other, b2Fixture* fixture, b2Fixture* otherFixture);
    virtual void endContact(GameObject* other, b2Fixture* fixture, b2Fixture* otherFixture);
};

#endif