#ifndef ENEMY1_HPP
#define ENEMY1_HPP
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Animation.hpp"

class Enemy1 : public GameObject
{
private:
    float damage;
    float moveSpeed;
    
    float guardTimeout;
    float guardTime = 0;
    
    float readyTimeout;
    float readyTime = 0;

    float walkTimeout;
    float walkTime  = 0;
    
    Animation<Enemy1AnimationEnum>* animation;
    b2Fixture* fixture;
public:
    Enemy1(b2World *world, sf::Vector2f spawnPosition);
    ~Enemy1();

    void processEvents(sf::Event event, sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
};

#endif