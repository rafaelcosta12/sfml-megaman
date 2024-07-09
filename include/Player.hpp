#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Animation.hpp"
#include "BasicShot.hpp"
#include <vector>

class Player : public GameObject
{
private:    
    b2Fixture* groundSensorFixture = NULL;
    b2Fixture* shapeFixture = NULL;

    bool isGrounded;
    float friction;
    float restitution;
    float density;
    float size[2];
    
    float jumpForce;

    float shotSpeed;
    float shotDelay;

    Animation<PlayerAnimation>* animation;
    std::vector<BasicShot*> projectiles;
protected:
    void recreateFixtures();
public:
    Player(b2World* world, float px, float py);
    ~Player();
    void processEvents(sf::Event event, sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
    void beginContact(GameObject* other, b2Fixture* fixture, b2Fixture* otherFixture) override;
    void endContact(GameObject* other, b2Fixture* fixture, b2Fixture* otherFixture) override;
};

#endif