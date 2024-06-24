#ifndef SPRITE_DEF_HPP
#define SPRITE_DEF_HPP
#include <SFML/Graphics.hpp>

class SpriteDef
{
private:
    sf::IntRect textureRect;
    float totalTime;
public:
    SpriteDef(sf::IntRect textureRect, float totalTime);
    ~SpriteDef();
    sf::IntRect getTextureRect();
    float getTotalTime();
};

#endif