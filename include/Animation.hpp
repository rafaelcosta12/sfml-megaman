#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "SpriteDef.hpp"
#include "PlayerAnimation.hpp"
#include "ShotAnimations.hpp"

template <typename T>
class Animation
{
private:
    sf::Sprite* sprite;
    sf::Texture* texture;
    float animTime;
    int animStep;
    T animCurrent;
    T animLast;
    float spriteSize;
    std::map<T, std::vector<SpriteDef>> animations;
public:
    float offset[2];
    Animation(std::string filename, float spriteSize, T initial);
    ~Animation();
    void update(float dt, b2Body* body);
    void render(sf::RenderWindow& window);
    void invertX();
    void setAnimation(T newAnimation, bool reset);
    sf::Vector2f getScale();
    T getLast();
    void addSprites(T sprite, int line, std::vector<float> timeSteps);
};

template class Animation<PlayerAnimation>;
template class Animation<BasicShotEnum>;

#endif