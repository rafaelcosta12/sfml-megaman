#ifndef BOX_HPP
#define BOX_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

class Box : public GameObject, public b2ContactListener
{
protected:
    b2Fixture* fixture;
    sf::RectangleShape shape;
public:
    Box(b2World* world, float px, float py, float sx, float sy);
    ~Box();
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
    void render(sf::RenderWindow& window) override;
};

#endif