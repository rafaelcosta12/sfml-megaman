#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Player.hpp"

class Camera : public GameObject
{
private:
    // main camera
    float offset[2];
    sf::Vector2f size;
    sf::View view;
    sf::FloatRect bounds;
    // free camera
    bool freeCam;
    float freeCamVelocity;
    float freeCamRatio;
    sf::Vector2f freeCamSize;
    sf::View freeCamView;
    //
    Player* player;
public:
    Camera(b2World* world, Player* player, sf::Vector2f spawn);
    ~Camera();
    void render(sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void processEvents(sf::Event event, sf::RenderWindow& window) override;
    void renderImgui();
    void setBounds(sf::FloatRect bounds);
};

#endif