#ifndef SCENARIO1_HPP
#define SCENARIO1_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Camera.hpp"
#include "Player.hpp"
#include "Met.hpp"
#include "Enemy.hpp"

#define ENEMIES_ARRAY_SIZE 32

class Scenario1 : public GameObject
{
protected:
    b2Fixture* fixture;
    sf::Sprite sprite;
    sf::Texture texture;
    Camera* camera;
    Player* player;
    std::vector<b2Fixture*> fixtures;
    sf::RectangleShape area1;
    Enemy* enemies[ENEMIES_ARRAY_SIZE];

    void addGroundFixture(b2Vec2* box);
    void createShape();
public:
    ~Scenario1();
    Scenario1(b2World* world, Player* player, float px, float py);
    void render(sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void processEvents(sf::Event event, sf::RenderWindow& window) override;
};

#endif