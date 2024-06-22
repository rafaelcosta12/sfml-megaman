#include "Game.hpp"
#include <box2d/box2d.h>

int main() {
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    Game game;
    game.run();
    return 0;
}