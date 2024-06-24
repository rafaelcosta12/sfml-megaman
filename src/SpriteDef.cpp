#include "SpriteDef.hpp"

SpriteDef::SpriteDef(sf::IntRect textureRect, float time)
{
    this->textureRect = textureRect;
    this->totalTime = time;
}

SpriteDef::~SpriteDef()
{
}

sf::IntRect SpriteDef::getTextureRect()
{
    return textureRect;
}

float SpriteDef::getTotalTime()
{
    return totalTime;
}
