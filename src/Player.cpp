#include "Player.hpp"
#include <iostream>
#include "imgui.h"
#include <vector>

Player::Player(b2World* world, float px, float py) : GameObject(world)
{
    size[0] = 21 * 0.05f / 2;
    size[1] = 24 * 0.05f / 2;

    name = "Player";
    
    friction = 0.0f;
    restitution = 0.0f;
    density = 10.0f;
    jumpForce = 14.0f;

    isGrounded = false;

    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.position.Set(px, -py);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    bodyDef.fixedRotation = true;
    body = world->CreateBody(&bodyDef);
    world->SetContactListener(this);

    recreateFixtures();

    // animation
    auto defs = std::map<PlayerAnimation, std::vector<SpriteDef>>();
    defs.insert(
        {
            PlayerAnimation::IDLE,
            std::vector<SpriteDef>({
                SpriteDef(sf::IntRect(3, 21, 21, 24), 2.0f),
                SpriteDef(sf::IntRect(28, 21, 21, 24), 0.25f),
            }),
        }
    );
    defs.insert(
        {
            PlayerAnimation::WALK,
            std::vector<SpriteDef>({
                SpriteDef(sf::IntRect(89, 21, 24, 22), 0.15f),
                SpriteDef(sf::IntRect(114, 21, 24, 24), 0.1f),
                SpriteDef(sf::IntRect(141, 21, 24, 24), 0.15f),
                SpriteDef(sf::IntRect(114, 21, 24, 24), 0.1f),
            }),
        }
    );
    defs.insert(
        {
            PlayerAnimation::JUMP,
            std::vector<SpriteDef>({
                SpriteDef(sf::IntRect(174, 13, 27, 30), 1.0f),
            }),
        }
    );
    animation = new Animation<PlayerAnimation>("../assets/megaman.png", PlayerAnimation::IDLE, defs);
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
}

void Player::update(float dt, sf::RenderWindow& window)
{
    float moveSpeed = 1.0f;
    float maxSpeed = 4.0f;

    b2Vec2 velocity = body->GetLinearVelocity();
    float desiredVelocity = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        animation->setAnimation(PlayerAnimation::WALK);
        desiredVelocity = -maxSpeed;

        if (animation->getScale().x < 0)
            animation->invertX();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        desiredVelocity = maxSpeed;
        animation->setAnimation(PlayerAnimation::WALK);
        
        if (animation->getScale().x > 0)
            animation->invertX();
    }
    else
    {
        animation->setAnimation(PlayerAnimation::IDLE);
    }

    float velocityChange = desiredVelocity - velocity.x;
    float force = body->GetMass() * velocityChange / 0.016f;

    // Aplicar a força horizontalmente
    body->ApplyForce(b2Vec2(force, 0), body->GetWorldCenter(), true);

    // Limitar a velocidade máxima
    if (fabs(body->GetLinearVelocity().x) > maxSpeed)
        body->SetLinearVelocity(b2Vec2((body->GetLinearVelocity().x > 0 ? maxSpeed : -maxSpeed), body->GetLinearVelocity().y));

    // pulo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && isGrounded)
        body->ApplyLinearImpulse(b2Vec2(0, jumpForce), body->GetWorldCenter(), true);
    
    if (!isGrounded)
        animation->setAnimation(PlayerAnimation::JUMP);
    
    // animation
    animation->update(dt, body);
}

void Player::render(sf::RenderWindow& window)
{
    // animation
    animation->render(window);

    GameObject::render(window);

    // imgui
    auto pos = body->GetPosition();
    ImGui::Begin("Player");
    ImGui::Text("Position: (%.3f, %.3f)", pos.x, -pos.y);
    ImGui::Text("Ground Contact: %s", isGrounded ? "true" : "false");
    ImGui::SliderFloat("Friction", &friction, 0, 1);
    ImGui::SliderFloat("Restitution", &restitution, 0, 1);
    ImGui::InputFloat("Density", &density, 0, 10000000.f);
    ImGui::SliderFloat("Jump Force", &jumpForce, 0, 50);
    bool applyPhysics = ImGui::Button("Apply");
    ImGui::End();

    if (applyPhysics)
    {
        auto pos = body->GetPosition();
        recreateFixtures();
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

void Player::BeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    if (fixtureA == groundSensorFixture || fixtureB == groundSensorFixture)
    {
        auto k = reinterpret_cast<GameObject*>(fixtureA->GetBody()->GetUserData().pointer);
        auto p = reinterpret_cast<GameObject*>(fixtureB->GetBody()->GetUserData().pointer);
        
        isGrounded = true;
    }
}

void Player::EndContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    if (fixtureA == groundSensorFixture || fixtureB == groundSensorFixture)
    {
        auto k = reinterpret_cast<GameObject*>(fixtureA->GetBody()->GetUserData().pointer);
        auto p = reinterpret_cast<GameObject*>(fixtureB->GetBody()->GetUserData().pointer);
        isGrounded = false;
    }
}

void Player::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}

void Player::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}
