#include <iostream>
#include "Animation.hpp"

template <typename T>
Animation<T>::Animation(std::string filename, float spriteSize, T initial)
{
    offset[0] = 0;
    offset[1] = 0;
    
    animStep = 0;
    animCurrent = initial;
    animLast = initial;

    texture = new sf::Texture();
    sprite = new sf::Sprite();

    this->spriteSize = spriteSize;

    if (!texture->loadFromFile(filename))
    {
        std::cout << "Erro ao abrir textura " + filename << std::endl;
    }

    sprite->setTexture(*texture, true);
    sprite->scale(sf::Vector2f(-0.05f, 0.05f));
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
    sprite->setOrigin((spriteSize + offset[0]) / 2, (spriteSize + offset[1]) / 2);
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
T Animation<T>::getLast()
{
    return animLast;
}

template <typename T>
void Animation<T>::addSprites(PlayerAnimation sprite, int line, std::vector<float> timeSteps)
{
    std::vector<SpriteDef> sprites;
    for (int i = 0; i < timeSteps.size(); i++)
    {
        sprites.push_back(SpriteDef(sf::IntRect(spriteSize * i, spriteSize * line, spriteSize, spriteSize), timeSteps[i]));
    }
    animations.insert({sprite, sprites});
}

template <typename T>
void Animation<T>::setAnimation(T newAnimation, bool reset)
{
    if (animCurrent == newAnimation)
        return;
    
    animLast = animCurrent;
    animCurrent = newAnimation;
    
    auto current = animations[animCurrent];
    
    if (current.size() == 0) return;

    if (reset) {
        animStep = 0;
        animTime = current.at(0).getTotalTime();
    }
    else {
        animStep = (animStep > current.size() - 1) ? 0 : animStep;
        animTime = current.at(animStep).getTotalTime();
    }
}
