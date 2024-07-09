#include "Player.hpp"
#include <iostream>
#include "imgui.h"
#include <vector>

Player::Player(b2World* world, float px, float py) : GameObject(world)
{
    name = "Player";
    tag = Tag::Player;

    size[0] = 0.4f;
    size[1] = 0.5f;
    isGrounded = false;
    friction = 0.0f;
    restitution = 0.0f;
    density = 10.0f;
    jumpForce = 30.0f;
    shotDelay = 0.0f;
    shotSpeed = 0.1f;

    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.position.Set(px, -py);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    bodyDef.fixedRotation = true;
    body = world->CreateBody(&bodyDef);

    recreateFixtures();

    animation = new Animation<PlayerAnimation>("../assets/spritesheet_megaman.png", 45, PlayerAnimation::IDLE);
    animation->addSprites(PlayerAnimation::IDLE, 0, std::vector<float>({2.0f, 0.25f}));
    animation->addSprites(PlayerAnimation::WALK, 1, std::vector<float>({0.15f, 0.1f, 0.15f}));
    animation->addSprites(PlayerAnimation::JUMP, 2, std::vector<float>({1.0f}));
    animation->addSprites(PlayerAnimation::IDLE_SHOT, 3, std::vector<float>({0.5f}));
    animation->addSprites(PlayerAnimation::WALK_SHOT, 4, std::vector<float>({0.15f, 0.1f, 0.15f}));
    animation->addSprites(PlayerAnimation::JUMP_SHOT, 5, std::vector<float>({0.5f}));
    animation->offset[1] = 10.0f;

    projectiles = std::vector<BasicShot*>();
}

Player::~Player()
{
}

void Player::processEvents(sf::Event event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    }

    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::K && shotDelay <= 0)
        {
            shotDelay = shotSpeed;
            projectiles.push_back(new BasicShot(world, getPosition(), animation->getScale().x < 0));
        }
    }

    // update projectiles
    for (auto shot : projectiles)
    {
        shot->processEvents(event, window);
    }
}

void Player::update(float dt, sf::RenderWindow& window)
{
    float moveSpeed = 1.0f;
    float maxSpeed = 4.0f;

    b2Vec2 velocity = body->GetLinearVelocity();
    float desiredVelocity = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        desiredVelocity = -maxSpeed;

        if (animation->getScale().x < 0)
            animation->invertX();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        desiredVelocity = maxSpeed;
        
        if (animation->getScale().x > 0)
            animation->invertX();
    }

    float velocityChange = desiredVelocity - velocity.x;
    float force = body->GetMass() * velocityChange / 0.016f;

    // Aplicar a força horizontalmente
    body->ApplyForce(b2Vec2(force, 0), body->GetWorldCenter(), true);

    // Limitar a velocidade máxima
    if (fabs(body->GetLinearVelocity().x) > maxSpeed)
        body->SetLinearVelocity(b2Vec2((body->GetLinearVelocity().x > 0 ? maxSpeed : -maxSpeed), body->GetLinearVelocity().y));

    // pulo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && isGrounded)
        body->ApplyLinearImpulse(b2Vec2(0, jumpForce), body->GetWorldCenter(), true);
    
    if (shotDelay > 0)
        shotDelay -= dt;
    
    // animation
    bool moving = desiredVelocity != 0;
    bool jumping = !isGrounded;
    bool shoting = shotDelay > 0;
    
    if (shoting)
        if (jumping)
            animation->setAnimation(PlayerAnimation::JUMP_SHOT, false);
        else
        if (moving)
            animation->setAnimation(PlayerAnimation::WALK_SHOT, false);
        else
            animation->setAnimation(PlayerAnimation::IDLE_SHOT, false);
    else
    if (jumping)
        animation->setAnimation(PlayerAnimation::JUMP, false);
    else
    if (moving)
        animation->setAnimation(PlayerAnimation::WALK, false);
    else
        animation->setAnimation(PlayerAnimation::IDLE, false);

    animation->update(dt, body);

    // update projectiles
    for (auto shot : projectiles)
    {
        shot->update(dt, window);
    }
}

void Player::render(sf::RenderWindow& window)
{
    // animation
    animation->render(window);

    GameObject::render(window);

    for (auto shot : projectiles)
    {
        shot->render(window);
    }

    // imgui
    auto pos = body->GetPosition();
    ImGui::Begin("Player");
    ImGui::Text("Position: (%.3f, %.3f)", pos.x, -pos.y);
    ImGui::Text("Ground Contact: %s", isGrounded ? "true" : "false");
    ImGui::SliderFloat("Friction", &friction, 0, 1);
    ImGui::SliderFloat("Restitution", &restitution, 0, 1);
    ImGui::InputFloat("Density", &density, 0, 10000000.f);
    ImGui::SliderFloat("Jump Force", &jumpForce, 0, 50);
    ImGui::SliderFloat("Shot Speed", &shotSpeed, 0, 1);
    ImGui::InputFloat2("Body Size", size);
    ImGui::SliderFloat2("Sprite Offset", animation->offset, -45, 45);
    bool applyPhysics = ImGui::Button("Apply");
    ImGui::End();

    if (applyPhysics)
    {
        auto pos = body->GetPosition();
        recreateFixtures();
    }
}

void Player::beginContact(GameObject* other, b2Fixture* fixture, b2Fixture* otherFixture)
{
    if (fixture == groundSensorFixture)
    {
        if (other->tag == Tag::Scenario)
            isGrounded = true;
    }

    if (other->tag == Tag::Enemy)
    {
        std::cout << "Contact with enemy" << std::endl;
        animation->setAnimation(PlayerAnimation::IDLE, true);
    }
}

void Player::endContact(GameObject *other, b2Fixture *fixture, b2Fixture *otherFixture)
{
    if (fixture == groundSensorFixture)
    {
        if (other->tag == Tag::Scenario)
            isGrounded = false;
    }
}

void Player::recreateFixtures()
{
    body->DestroyFixture(shapeFixture);
    body->DestroyFixture(groundSensorFixture);


    // shape fixture
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(size[0], size[1]);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    fixtureDef.density = density;
    shapeFixture = body->CreateFixture(&fixtureDef);

    // ground sensor fixture
    b2PolygonShape groundSensorShape;
    groundSensorShape.SetAsBox(size[0] * 0.7f, 0.1f, b2Vec2(0, -size[1]), 0);
    b2FixtureDef groundSensorFixtureDef;
    groundSensorFixtureDef.shape = &groundSensorShape;
    groundSensorFixtureDef.isSensor = true;
    groundSensorFixture = body->CreateFixture(&groundSensorFixtureDef);
}
