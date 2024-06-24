#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "SpriteDef.hpp"
#include "PlayerAnimation.hpp"

template <typename T>
class Animation
{
private:
    sf::Sprite* sprite;
    sf::Texture* texture;
    float animTime;
    int animStep;
    T animCurrent;
    std::map<T, std::vector<SpriteDef>> animations;
public:
    Animation(std::string filename, T initial, std::map<T, std::vector<SpriteDef>> animations);
    ~Animation();
    void update(float dt, b2Body* body);
    void render(sf::RenderWindow& window);
    void invertX();
    sf::Vector2f getScale();
    void setAnimation(T newAnimation);
};

template class Animation<PlayerAnimation>;

#endif