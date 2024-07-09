#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "GameObject.hpp"
#include "Animation.hpp"

class Enemy : public GameObject
{
protected:
    float damage;
    float moveSpeed;
    float hp;

    Animation<Enemy1AnimationEnum>* animation;
public:
    Enemy(b2World* world, sf::Vector2f spawnPosition);
    ~Enemy();
    virtual void processEvents(sf::Event event, sf::RenderWindow& window);
    virtual void update(float dt, sf::RenderWindow& window);
    virtual void render(sf::RenderWindow& window);
    virtual void beginContact(GameObject* other, b2Fixture* fixture, b2Fixture* otherFixture);
    virtual void endContact(GameObject* other, b2Fixture* fixture, b2Fixture* otherFixture);
    virtual bool isDeath();
    virtual void destroy();
};

#endif