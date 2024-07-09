#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <box2d/box2d.h>
#include "GameObject.hpp"
#include "ContactsHandler.hpp"

class Game {
public:
    Game();
    void run();
private:
    void processEvents();
    void update(float dt);
    void render();

    sf::RenderWindow window;
    sf::Clock clock;
    std::vector<GameObject*> gameObjects;
    b2World* world;
    ContactsHandler* contactHandler;
};

#endif // GAME_HPP