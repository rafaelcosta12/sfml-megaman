#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class GameObject
{
protected:
    b2World* world;
    b2Body* body = NULL;
public:
    std::string name = "unknow";
    GameObject(b2World* world);
    ~GameObject();
    
    virtual void processEvents(sf::Event event, sf::RenderWindow& window);
    virtual void update(float dt, sf::RenderWindow& window);
    virtual void render(sf::RenderWindow& window);
    virtual sf::Vector2f getPosition();
};

#endif