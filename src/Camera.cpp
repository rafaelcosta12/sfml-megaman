#include "Camera.hpp"
#include "imgui.h"
#include <iostream>

Camera::Camera(b2World* world, float px, float py) : GameObject(world)
{
    ratio = 1.0f;
    size[0]  = 10.0f;
    size[1] = 10.0f * 0.75f;
    position[0] = px;
    position[1] = py;
    freeCam = false;
    freeCamVelocity = 0.1f;
}

Camera::~Camera()
{
}

void Camera::processEvents(sf::Event event, sf::RenderWindow& window)
{
    if (!freeCam) return;

    auto step = freeCamVelocity * 0.016f;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        position[0] -= step;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        position[0] += step;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        position[1] += step;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        position[1] -= step;
}

void Camera::setCenter(sf::Vector2f center)
{
    position[0] = center.x, position[1] = center.y;
}

void Camera::render(sf::RenderWindow& window)
{
    sf::View view;
    view.setCenter(sf::Vector2f(position[0], position[1]));
    view.setSize(sf::Vector2f(size[0] * ratio, size[1] * ratio));
    window.setView(view);

    ImGui::Begin("Camera");
    ImGui::InputFloat2("Posição", position, "%.3f");
    ImGui::SliderFloat("Proporção", &ratio, 0, 50);
    ImGui::Checkbox("Free Cam", &freeCam);
    ImGui::SliderFloat("Free Cam Velocity", &freeCamVelocity, 0, 1000);
    ImGui::End();
}
