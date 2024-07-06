#ifndef BASIC_SHOT_HPP
#define BASIC_SHOT_HPP
#include "GameObject.hpp"
#include "Animation.hpp"

class BasicShot : public GameObject
{
private:
    float damage;
    float speed;
    b2Fixture* fixture;
    Animation<BasicShotEnum>* animation;
    
    void createBody(sf::Vector2f spanwPosition, bool lookingRight);
public:
    BasicShot(b2World* world, sf::Vector2f spanwPosition, bool lookingRight);
    ~BasicShot();
    void processEvents(sf::Event event, sf::RenderWindow &window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
};

#endif