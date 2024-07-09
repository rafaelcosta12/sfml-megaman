#ifndef ENEMY1_HPP
#define ENEMY1_HPP
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Animation.hpp"
#include "enemies/Enemy.hpp"

class Met : public Enemy
{
private:
    float cooldown = 0;
    
    float guardTimeout;
    float guardTime = 0;
    
    float readyTimeout;
    float readyTime = 0;

    float walkTimeout;
    float walkTime  = 0;

    b2Fixture* fixture;
public:
    Met(b2World *world, sf::Vector2f spawnPosition);
    ~Met();

    void processEvents(sf::Event event, sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
    void beginContact(GameObject* other, b2Fixture* fixture, b2Fixture* otherFixture) override;
    void endContact(GameObject* other, b2Fixture* fixture, b2Fixture* otherFixture) override;
};

#endif