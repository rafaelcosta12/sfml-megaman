#include "ContactsHandler.hpp"
#include "GameObject.hpp"

ContactsHandler::ContactsHandler()
{
}

ContactsHandler::~ContactsHandler()
{
}

void ContactsHandler::BeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    auto A = reinterpret_cast<GameObject*>(fixtureA->GetBody()->GetUserData().pointer);
    auto B = reinterpret_cast<GameObject*>(fixtureB->GetBody()->GetUserData().pointer);

    A->beginContact(B, fixtureA, fixtureB);
    B->beginContact(A, fixtureB, fixtureA);
}

void ContactsHandler::EndContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    auto A = reinterpret_cast<GameObject*>(fixtureA->GetBody()->GetUserData().pointer);
    auto B = reinterpret_cast<GameObject*>(fixtureB->GetBody()->GetUserData().pointer);

    A->endContact(B, fixtureA, fixtureB);
    B->endContact(A, fixtureB, fixtureA);
}

void ContactsHandler::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}

void ContactsHandler::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}

bool ContactsHandler::ShouldCollide(b2Fixture *fixtureA, b2Fixture *fixtureB)
{
    auto A = reinterpret_cast<GameObject*>(fixtureA->GetBody()->GetUserData().pointer);
    auto B = reinterpret_cast<GameObject*>(fixtureB->GetBody()->GetUserData().pointer);
    
    auto containsPlayer = A->tag == Tag::Player || B->tag == Tag::Player;
    auto containsEnemy = A->tag == Tag::Enemy || B->tag == Tag::Enemy;

    if (containsPlayer && containsEnemy)
        return false;
    
    return true;
}
