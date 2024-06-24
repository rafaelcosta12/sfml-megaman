#ifndef SCENARIO1_HPP
#define SCENARIO1_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

class Scenario1 : public GameObject
{
protected:
    b2Fixture* fixture;
    sf::Sprite sprite;
    sf::Texture texture;
    void createShape();
public:
    ~Scenario1();
    Scenario1(b2World* world, float px, float py);
    void render(sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
};

#endif