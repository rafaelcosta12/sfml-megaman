#include "Game.hpp"
#include "Player.hpp"
#include "Scenario1.hpp"
#include "Box.hpp"
#include "Camera.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"

Game::Game() : window(sf::VideoMode(800, 600), "Example")
{
    srand(static_cast<unsigned int>(time(0)));
    window.setFramerateLimit(60);
    
    b2Vec2 gravity(0.0f, -20.0f);
    world = new b2World(gravity);

    auto player = new Player(world, 4.9875f, 97.3125f);
    gameObjects.push_back(new Scenario1(world, player, 0,99.2938f+2.0f));
}

void Game::run()
{
    if (!ImGui::SFML::Init(window))
        return;

    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    while (window.isOpen())
    {
        world->Step(timeStep, velocityIterations, positionIterations);
        processEvents();
        update(clock.restart().asSeconds());
        render();
    }

    ImGui::SFML::Shutdown();
}

void Game::processEvents()
{
    sf::Event event;
    
    while (window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(window, event);
        
        if (event.type == sf::Event::Closed)
            window.close();

        for (auto& i : gameObjects)
            i->processEvents(event, window);

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                std::cout << position.x << ", " << position.y << std::endl;
            }

            if (event.mouseButton.button == sf::Mouse::Right)
            {
                sf::Vector2f position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                gameObjects.push_back(new Box(world, position.x, position.y, 0.5, 0.5));
            }
        }
    }
}

void Game::update(float dt)
{
    for (auto& g : gameObjects)
    {
        g->update(dt, window);
    }
}

void Game::render()
{
    window.clear();

    ImGui::SFML::Update(window, clock.restart());

    for (auto &o : gameObjects)
    {
        o->render(window);
    }
    
    ImGui::SFML::Render(window);
    window.display();
}