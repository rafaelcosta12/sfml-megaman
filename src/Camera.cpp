#include "Camera.hpp"
#include "imgui.h"
#include <iostream>

Camera::Camera(b2World* world, Player* player, sf::Vector2f spawn) : GameObject(world)
{
    this->player = player;

    // main camera
    float const ratio = 1.4f;
    size = sf::Vector2f(10.0f * ratio, 10.0f * 0.75f * ratio);
    view.setCenter(spawn);
    view.setSize(size);
    offset[0] = 0.f, offset[1] = 0.f;

    // free cam
    freeCam = false;
    freeCamVelocity = 10.0f;
    freeCamRatio = 2.0f;
    freeCamSize = sf::Vector2f(10.0f, 10.0f * 0.75f);
    freeCamView.setCenter(spawn);
    freeCamView.setSize(freeCamSize);
}

Camera::~Camera()
{
}

void Camera::processEvents(sf::Event event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::EventType::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Space)
            freeCam = !freeCam;
    }
}

void Camera::renderImgui()
{
    if (!freeCam) return;
    ImGui::Begin("Camera livre");
    ImGui::SliderFloat("Proporção", &freeCamRatio, 1, 10);
    ImGui::SliderFloat("Free Cam Velocity", &freeCamVelocity, 0, 1000);
    ImGui::End();

    freeCamView.setSize(freeCamSize * freeCamRatio);
}

void Camera::setBounds(sf::FloatRect bounds)
{
    this->bounds = bounds;
}

void Camera::render(sf::RenderWindow& window)
{
    window.setView(freeCam ? freeCamView : view);

    if (freeCam)
    {
        auto size = view.getSize();
        sf::RectangleShape mainCameraArea(size);
        mainCameraArea.setOrigin(size * 0.5f);
        mainCameraArea.setPosition(view.getCenter());
        mainCameraArea.setFillColor(sf::Color::Transparent);
        mainCameraArea.setOutlineColor(sf::Color::Magenta);
        mainCameraArea.setOutlineThickness(0.1f);
        
        window.draw(mainCameraArea);
    }

    renderImgui();
}

void Camera::update(float dt, sf::RenderWindow &window)
{
    auto playerPosition = player->getPosition();
    auto mSize = size * 0.5f;
    
    if (playerPosition.x - mSize.x < bounds.left)
        playerPosition.x = bounds.left + mSize.x;
    
    if (playerPosition.x + mSize.x > bounds.left + bounds.width)
        playerPosition.x = bounds.left + bounds.width - mSize.x;
    
    if (playerPosition.y - mSize.y < bounds.top)
        playerPosition.y = bounds.top + mSize.y;
    
    if (playerPosition.y + mSize.y > bounds.top + bounds.height)
        playerPosition.y = bounds.top + bounds.height - mSize.y;
    
    view.setCenter(playerPosition);

    if (!freeCam) return;

    auto step = freeCamVelocity * 0.016f;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        freeCamView.move(-step, 0);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        freeCamView.move(step, 0);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        freeCamView.move(0, -step);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        freeCamView.move(0, step);
}
