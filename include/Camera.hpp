#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

class Camera : public GameObject
{
private:
    float ratio;
    float position[2];
    float size[2];
    float freeCamVelocity;
    bool freeCam;
public:
    Camera(b2World* world, float px, float py);
    ~Camera();
    void render(sf::RenderWindow& window) override;
    void processEvents(sf::Event event, sf::RenderWindow& window) override;
    void setCenter(sf::Vector2f center);
};

#endif