#include <iostream>
#include "Animation.hpp"

template <typename T>
Animation<T>::Animation(std::string filename, T initial, std::map<T, std::vector<SpriteDef>> animations)
{
    texture = new sf::Texture();
    sprite = new sf::Sprite();

    this->animations = animations;
    if (!texture->loadFromFile(filename))
    {
        std::cout << "Erro ao abrir textura " + filename << std::endl;
    }
    sprite->setTexture(*texture, true);
    sprite->scale(sf::Vector2f(-0.05f, 0.05f));
    sprite->setOrigin(21/2, 24/2);

    setAnimation(initial);
}

template <typename T>
Animation<T>::~Animation()
{
}

template <typename T>
void Animation<T>::update(float dt, b2Body* body)
{
    animTime -= dt;
    if (animTime < 0)
    {
        auto curr = animations[animCurrent];
        animStep = (animStep + 1) % curr.size();
        animTime =  curr[animStep].getTotalTime();
    }
    sprite->setPosition(body->GetPosition().x, -body->GetPosition().y);
}

template <typename T>
void Animation<T>::render(sf::RenderWindow &window)
{
    sprite->setTextureRect(animations[animCurrent].at(animStep).getTextureRect());
    window.draw(*sprite);
}

template <typename T>
void Animation<T>::invertX()
{
    sprite->scale(sf::Vector2f(-1, 1));
}

template <typename T>
sf::Vector2f Animation<T>::getScale()
{
    return sprite->getScale();
}

template <typename T>
void Animation<T>::setAnimation(T newAnimation)
{
    if (animCurrent == newAnimation) return;
    animCurrent = newAnimation;
    animStep = 0;
    animTime = animations[animCurrent].at(animStep).getTotalTime();
}
