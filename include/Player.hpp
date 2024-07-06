#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Animation.hpp"
#include "BasicShot.hpp"
#include <vector>

class Player : public GameObject, public b2ContactListener
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
    // game object
    void processEvents(sf::Event event, sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
    // contact listener
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
};

#endif